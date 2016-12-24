
#ifndef _CLAL_CLCONTEXT_HPP_
#define _CLAL_CLCONTEXT_HPP_

#include <vector>

#include "CLReferenceCount.hpp"
#include "CLDevice.hpp"
#include "CLCommandQueue.hpp"

namespace CLAL {


	class CLContext : public ReferenceCount<cl_context, clRetainContext, clReleaseContext> {



	private:
		std::vector<CLDevice>       devices;
		std::vector<CLCommandQueue> commandQueues;

	};


}




#endif


