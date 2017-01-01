#ifndef _CLAL_CLKERNEL_HPP
#define _CLAL_CLKERNEL_HPP

#include "CLReferenceCount.hpp"



namespace CLAL {

	class Parameter;

	class CLKernel : public ReferenceCount<cl_kernel, clRetainKernel, clReleaseKernel> {


	public:

		// note: used internally, need to release it manually
		static CLKernel create(cl_kernel kernel);


		// for CLProgram (kernelTable)
		CLKernel() = default;
		CLKernel(const CLKernel&) = default;
		//CLKernel(CLKernel&&) = default;
		CLKernel& operator= (CLKernel&&) = default;

		// Set kernel arguments for raw pointer
		virtual void setArg(unsigned int index, size_t size, void* ptr);

		// primitives
		virtual void setArg(unsigned int index, Parameter param);


		virtual ~CLKernel();

	private:

		// OpenCL Kernel Wrapper
		CLKernel(cl_kernel kernel);
	};



}








#endif
