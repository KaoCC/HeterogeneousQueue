#ifndef _CLAL_CLCOMMANDQUEUE_HPP_
#define _CLAL_CLCOMMANDQUEUE_HPP_


#include "CLReferenceCount.hpp"


#include "CLDevice.hpp"
#include "CLContext.hpp"



namespace CLAL {

//	class CLDevice;
	class CLContext;

	class CLCommandQueue : public ReferenceCount<cl_command_queue, clRetainCommandQueue, clReleaseCommandQueue> {

	public:

		static CLCommandQueue create(CLDevice device, CLContext context);
		static CLCommandQueue create(cl_command_queue cq);

		CLCommandQueue();

		virtual ~CLCommandQueue();


	private:

		//wrap OpenCL CommandQueue
		CLCommandQueue(cl_command_queue cmdQueue);




	};



}









#endif


