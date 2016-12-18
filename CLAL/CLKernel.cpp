#include "CLKernel.hpp"


namespace CLAL {


	CLKernel::CLKernel(cl_kernel kernel) : ReferenceCount<cl_kernel, clRetainKernel, clReleaseKernel>(kernel) {

	}

	CLKernel::~CLKernel() {
	}

}
