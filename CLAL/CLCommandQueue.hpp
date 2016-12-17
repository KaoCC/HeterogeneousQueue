#ifndef _CLAL_CLCOMMANDQUEUE_HPP_
#define _CLAL_CLCOMMANDQUEUE_HPP_


#include "CLReferenceCount.hpp"



namespace CLAL {



	class CLCommandQueue : public ReferenceCount<cl_command_queue, clRetainCommandQueue, clReleaseCommandQueue> {

	public:
		CLCommandQueue();

		virtual ~CLCommandQueue();


	private:

		//wrap OpenCL CommandQueue
		CLCommandQueue(cl_command_queue cmdQueue);




	};



}









#endif