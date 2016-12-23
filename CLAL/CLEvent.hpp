

#ifndef _CLAL_CLEVENT_HPP_
#define _CLAL_CLEVENT_HPP_

#include "CLReferenceCount.hpp"

namespace CLAL {

	class CLEvent : public ReferenceCount<cl_event, clRetainEvent, clReleaseEvent> {




	};

}



#endif