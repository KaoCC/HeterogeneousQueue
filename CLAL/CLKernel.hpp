#ifndef _CLAL_CLKERNEL_HPP
#define _CLAL_CLKERNEL_HPP

#include "CLReferenceCount.hpp"



namespace CLAL {

	class CLKernel : public ReferenceCount<cl_kernel, clRetainKernel, clReleaseKernel> {


	public:
		virtual ~CLKernel();

	private:

		// OpenCL Kernel Wrapper
		CLKernel(cl_kernel kernel);
	};



}








#endif
