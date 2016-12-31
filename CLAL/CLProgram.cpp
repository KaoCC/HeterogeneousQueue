#include "CLProgram.hpp"
#include "CLException.hpp"
#include "CLContext.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

namespace CLAL {


	static void LoadFromFile(const std::string fileName, std::vector<char>& outputBuffer) {

		// KAOCC: binary mode as default
		std::ifstream file(fileName, std::ios::binary);


		// might cause performance issue
		// should get the lengh of the file and reserve the size
		outputBuffer.assign((std::istreambuf_iterator<char>(file)),
			std::istreambuf_iterator<char>());
	}


	CLProgram CLProgram::createFromSource(const CLContext& context, char const * sourcecode, size_t sourcesize, char const * buildopts) {

		cl_int status = CL_SUCCESS;

		// Create program
		//KAOCC:  double check this one
		cl_program tmpProgram = clCreateProgramWithSource(context, 1, (const char**)&sourcecode, &sourcesize, &status);

		ThrowIfCL(status != CL_SUCCESS, status, "clCreateProgramWithSource failed");

		std::vector<cl_device_id> deviceIds(context.getDeviceCount());
		for (unsigned int i = 0; i < context.getDeviceCount(); ++i) {
			deviceIds[i] = context.getDevice(i);
		}


		// Build program
		status = clBuildProgram(tmpProgram, context.getDeviceCount(), deviceIds.data(), buildopts, nullptr, nullptr);

		// report the status and throw exceptions if failed
		// KAOCC: need to double check
		if (status != CL_SUCCESS) {
			std::vector<char> buildLog;
			size_t logSize = 0;

			clGetProgramBuildInfo(tmpProgram, deviceIds[0], CL_PROGRAM_BUILD_LOG, 0, nullptr, &logSize);

			buildLog.resize(logSize);
			clGetProgramBuildInfo(tmpProgram, deviceIds[0], CL_PROGRAM_BUILD_LOG, logSize, buildLog.data(), nullptr);

			std::cerr << buildLog.data() << std::endl;

			throw CLException(status, std::string(buildLog.data()));
		}



		CLProgram retProgram(tmpProgram);

		// need to release the program we create internally
		clReleaseProgram(tmpProgram);

		return retProgram;
	}

	CLProgram CLProgram::createFromFileName(const CLContext & context, char const * filename, char const * buildopts) {

		std::vector<char> source;
		LoadFromFile(filename, source);
		return createFromSource(context, source.data(), source.size(), buildopts);
	}


	size_t CLProgram::getKernelCount() const {
		return kernelTable.size();
	}

	CLKernel CLProgram::GetKernel(std::string const & funcName) const {

		auto iter = kernelTable.find(funcName);

		ThrowIfCL(iter == kernelTable.end(), CL_INVALID_KERNEL_NAME, "No such kernel in program");

		// copy
		return iter->second;

	}

	CLProgram::~CLProgram() {
	}


	// YET TO BE DONE !!
	CLProgram::CLProgram(cl_program program) :
		ReferenceCount<cl_program, clRetainProgram, clReleaseProgram>(program) {

		

		// get number of Kernels
		cl_uint numKernels = 0;
		cl_int status = clCreateKernelsInProgram(*this, 0, nullptr, &numKernels);

		// KAOCC: can we throw from this ctor ?
		ThrowIfCL(numKernels == 0, CL_BUILD_ERROR, "clCreateKernelsInProgram: no kernels available ?");
		ThrowIfCL(status != CL_SUCCESS, status, "clCreateKernelsInProgram failed");


		// Create Kernels
		std::vector<cl_kernel> kernels(numKernels);
		status = clCreateKernelsInProgram(*this, numKernels, kernels.data(), nullptr);

		ThrowIfCL(status != CL_SUCCESS, status, "clCreateKernelsInProgram failed");

		// Store in KernelTable
		std::for_each(kernels.begin(), kernels.end(), [this](cl_kernel ker) {

			size_t size = 0;
			// get size
			cl_int res = clGetKernelInfo(ker, CL_KERNEL_FUNCTION_NAME, 0, nullptr, &size);
			ThrowIfCL(res != CL_SUCCESS, res, "clGetKernelInfo failed");

			std::vector<char> temp(size);
			// get name
			res = clGetKernelInfo(ker, CL_KERNEL_FUNCTION_NAME, size, temp.data(), nullptr);
			ThrowIfCL(res != CL_SUCCESS, res, "clGetKernelInfo failed");

			std::string funcName(temp.begin(), temp.end() - 1);
			kernelTable[funcName] = std::move(CLKernel::create(ker));
		});

	}

}
