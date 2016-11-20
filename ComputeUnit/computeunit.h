
#pragma once
#include <CL/cl.h>

#include <vector>
#include <string>

namespace hqueue {

	class ComputeUnit {


	public:

		// 2. Define a public static accessor function
		static ComputeUnit* get_instance();


		cl_context& get_context();
		cl_command_queue& get_commandQueue();
		cl_kernel& get_kernel(unsigned int index);

	private:

		// 4. Define all ctors to be protected or private
		ComputeUnit(const std::string kernel_path[], size_t length);

		// Singleton Design Pattern
		// 1. Define a private static attribute (instance)
		static ComputeUnit* cu_instance;


		// OpenCL member
		cl_context gpuContext;
		cl_command_queue gpuCommandQueue;

		//cl_kernel gpuKernel;
		std::vector<cl_kernel> gpuKernels;

		size_t workGroupSize;

		// helper function
		cl_program load_program(cl_context& context, const std::string& fileName);


	};



	// SVM allocation

	void* svmalloc(int size);
	void svmfree(void* ptr);
	void* align_svmalloc(int size);

}
