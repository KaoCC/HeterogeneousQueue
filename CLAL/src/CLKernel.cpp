#include "CLKernel.hpp"
#include "CLException.hpp"

namespace CLAL {


	CLKernel::CLKernel(cl_kernel kernel) : ReferenceCount<cl_kernel, clRetainKernel, clReleaseKernel>(kernel) {

	}

	// KAOCC: kernels are intended to be used internally. So we need to release them manually.
	CLKernel CLKernel::create(cl_kernel kernel) {

		CLKernel retKernel(kernel);
		clReleaseKernel(kernel);
		return retKernel;
	}

	CLKernel::~CLKernel() {
	}

	// KAOCC: This is for universal pointer types.
	void CLKernel::setArg(unsigned int index, size_t size, void * ptr) {

		cl_int status = clSetKernelArg(*this, index, size, ptr);
		ThrowIfCL(status != CL_SUCCESS, status, "clSetKernelArg failed");
	}

}
