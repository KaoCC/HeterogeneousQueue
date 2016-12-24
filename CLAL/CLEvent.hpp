

#ifndef _CLAL_CLEVENT_HPP_
#define _CLAL_CLEVENT_HPP_

#include "CLReferenceCount.hpp"

namespace CLAL {

	class CLEvent : public ReferenceCount<cl_event, clRetainEvent, clReleaseEvent> {

	public:


		//static CLEvent create(cl_event);


		CLEvent();

		void  wait();
		float getDuration() const;
		cl_int getCommandExecutionStatus() const;


		virtual ~CLEvent();

	private:
		CLEvent(cl_event program);


	};

}



#endif