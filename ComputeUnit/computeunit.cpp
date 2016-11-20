
#include <vector>
#include <iostream>
#include <fstream>

#include "common/sys/platform.h"

#include "computeunit.h"


namespace hqueue {


	ComputeUnit* ComputeUnit::cu_instance = nullptr;

// test
	const size_t KERNEL_PATH_COUNT = 3;
	const std::string kernel_path[] = { "opencl20.cl", "doubleindex.cl", "lookup.cl" };

	ComputeUnit* ComputeUnit::get_instance()
	{
		// 3. Do "lazy initialization" in the accessor function
		if (!cu_instance) {
			cu_instance = new ComputeUnit(kernel_path, KERNEL_PATH_COUNT );
		}

		return cu_instance;
	}


	// Access function


	cl_context& ComputeUnit::get_context() {
		return this->gpuContext;
	}

	cl_command_queue& ComputeUnit::get_commandQueue() {
		return this->gpuCommandQueue;
	}

	cl_kernel& ComputeUnit::get_kernel(unsigned int index) {
		return this->gpuKernels[index];
	}


	void* svmalloc(int size){
		// TODO: fix
		return align_svmalloc(size);
	}

	void svmfree(void* ptr) {
		clSVMFree(ComputeUnit::get_instance()->get_context(), ptr);
	}

	void* align_svmalloc(int size){
	        char* base = static_cast<char*>(clSVMAlloc(ComputeUnit::get_instance()->get_context(), CL_MEM_SVM_FINE_GRAIN_BUFFER, size + 64 + sizeof(int), 0));
	        char* unaligned = base + sizeof(int);
	        char*   aligned = unaligned + 64 - ((size_t)unaligned & (63));
	        ((int*)aligned)[-1] = (int)((size_t)aligned-(size_t)base);

			// TODO: bug !
	        return (void*)base;
	}

	// for C compatibility

	ComputeUnit::ComputeUnit(const std::string kernel_path[], size_t length) : workGroupSize(0) {
		//Step1: Getting platforms and choose an available one.
		cl_uint numPlatforms;   //the NO. of platforms
		cl_platform_id gpuPlatform = NULL; //the chosen platform
		cl_int  status = clGetPlatformIDs(0, NULL, &numPlatforms);
		if (status != CL_SUCCESS) {
			std::cout << "Error: Getting platforms!" << std::endl;
			return;
		}
		if (numPlatforms > 0) {
			cl_platform_id* platforms = (cl_platform_id*)alignedMalloc(numPlatforms* sizeof(cl_platform_id));
			status = clGetPlatformIDs(numPlatforms, platforms, NULL);
			gpuPlatform = platforms[1];
			alignedFree(platforms);
		}

		//Step 2:Query the platform and choose the first GPU device if has one.Otherwise use the CPU as device.
		cl_uint             numDevices = 0;
		cl_device_id        *gpuDevices;
		status = clGetDeviceIDs(gpuPlatform, CL_DEVICE_TYPE_GPU, 0, NULL, &numDevices);

		std::cout << "Choose GPU device." << std::endl;
		gpuDevices = (cl_device_id*)alignedMalloc(numDevices * sizeof(cl_device_id));
		status = clGetDeviceIDs(gpuPlatform, CL_DEVICE_TYPE_GPU, numDevices, gpuDevices, NULL);

		//Step 3: Create context.
		gpuContext = clCreateContext(NULL, 1, gpuDevices, NULL, NULL, &status);
		if (status != CL_SUCCESS) {
			printf("gpuContext error %d\n", status);
			clReleaseContext(gpuContext);
			return;
		}
		size_t cb;
		clGetContextInfo(gpuContext, CL_CONTEXT_DEVICES, 0, NULL, &cb);
		std::vector<cl_device_id> devicess(cb / sizeof(cl_device_id));
		clGetContextInfo(gpuContext, CL_CONTEXT_DEVICES, cb, &devicess[0], 0);

		clGetDeviceInfo(devicess[0], CL_DEVICE_NAME, 0, NULL, &cb);
		std::string devname;
		devname.resize(cb);
		clGetDeviceInfo(devicess[0], CL_DEVICE_NAME, cb, &devname[0], 0);
		std::cout << "GPU Device: " << devname.c_str() << "\n";

		//Step 4: Creating command queue associate with the context.
		gpuCommandQueue = clCreateCommandQueue(gpuContext, gpuDevices[0], 0, &status);
		if (status != CL_SUCCESS) {
			std::cerr << "gpuCommandQueue error\n";
			clReleaseCommandQueue(gpuCommandQueue);
			clReleaseContext(gpuContext);
			return;
		}

		for (size_t m = 0; m < length; ++m) {

			cl_program gpuProgram = load_program(gpuContext, kernel_path[m]);
			if (gpuProgram == 0) {
				std::cerr << "Can't load or build gpuProgram:" << kernel_path[m] << std::endl;
				char *program_log;
				size_t log_size;
				/* Find size of log and print to std output */
				clGetProgramBuildInfo(gpuProgram, gpuDevices[0], CL_PROGRAM_BUILD_LOG,
					0, NULL, &log_size);
				program_log = (char*)malloc(log_size + 1);
				program_log[log_size] = '\0';
				clGetProgramBuildInfo(gpuProgram, gpuDevices[0], CL_PROGRAM_BUILD_LOG,
					log_size + 1, program_log, NULL);
				printf("%s\n", program_log);
				free(program_log);
				clReleaseCommandQueue(gpuCommandQueue);
				clReleaseContext(gpuContext);
				return;
			}

			cl_kernel gpuKernel = clCreateKernel(gpuProgram, "intersect", &status);
			if (status != CL_SUCCESS) {
				std::cerr << "Can't create gpuKernel:" << kernel_path[m] << std::endl;
				clReleaseCommandQueue(gpuCommandQueue);
				clReleaseContext(gpuContext);
				return;
			}

			// push to vector
			this->gpuKernels.push_back(gpuKernel);

		}

		//char* base = (char*)clSVMAlloc(gpuContext, CL_MEM_SVM_FINE_GRAIN_BUFFER, sizeof(Ray) * 262144 + 64 + sizeof(int), 0);
		//char* unaligned = base + sizeof(int);
		//char*   aligned = unaligned + 64 - ((size_t)unaligned & (63));
		//((int*)aligned)[-1] = (int)((size_t)aligned - (size_t)base);

		//svmRay = (Ray*)aligned;
	};




	cl_program ComputeUnit::load_program(cl_context& context, const std::string& fileName) {
		std::fstream file;
		file.exceptions(std::ifstream::eofbit | std::ifstream::failbit | std::ifstream::badbit);
		file.open(fileName.c_str(), std::fstream::in | std::fstream::binary);

		std::string program_source(std::istreambuf_iterator<char>(file), (std::istreambuf_iterator<char>()));

		// create and build program 
		const char* source = program_source.c_str();
		int error;
		cl_program program = clCreateProgramWithSource(context, 1, &source, 0, &error);
		if (error != CL_SUCCESS) {
			printf("program error");
			return 0;
		}

		if (clBuildProgram(program, 0, 0, "", 0, 0) != CL_SUCCESS) {
			std::cerr << "Build Error" << std::endl;
			return 0;
		}

		return program;
	}



}