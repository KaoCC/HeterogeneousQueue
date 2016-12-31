

#ifndef _CLAL_CLEVENT_HPP_
#define _CLAL_CLEVENT_HPP_

#include "CLReferenceCount.hpp"

namespace CLAL {

	class CLEvent : public ReferenceCount<cl_event, clRetainEvent, clReleaseEvent> {

	public:

		// wrap cl_event
		// need to release it manually since we used it internally in this layer
		static CLEvent create(cl_event evt);


		CLEvent() = delete;

		void  wait();
		float getDuration() const;
		cl_int getCommandExecutionStatus() const;


		virtual ~CLEvent();

	private:
		CLEvent(cl_event evt);


	};

}



#endif