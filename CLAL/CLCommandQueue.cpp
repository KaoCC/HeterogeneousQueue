#include "CLCommandQueue.hpp"

namespace CLAL {

	CLCommandQueue CLCommandQueue::create(cl_command_queue cq) {
		return CLCommandQueue(cq);
	}

	CLCommandQueue CLCommandQueue::create(CLDevice device, CLContext context) {



		cl_int status = CL_SUCCESS;
		cl_command_queue cq = clCreateCommandQueue(context, device, CL_QUEUE_PROFILING_ENABLE, &status);
		ThrowIfCL(status != CL_SUCCESS, status, "clCreateCommandQueue failed");

		CLCommandQueue cmdQueue(cq);
		clReleaseCommandQueue(cq);

		return cmdQueue;
	}

	CLCommandQueue::CLCommandQueue() {
	}

	CLAL::CLCommandQueue::~CLCommandQueue() {
	}

}
