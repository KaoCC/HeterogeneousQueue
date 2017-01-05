#include "EventCLImpl.hpp"
#include "ExceptionCLImpl.hpp"
#include "CLEvent.hpp"
#include "CLException.hpp"

namespace CE {

	void EventCLImpl::wait() {

		try {
			event.wait();

		} catch (CLAL::CLException& e) {
			throw ExceptionCLImpl(e.what());
		}
	}


	bool EventCLImpl::isComplete() const {


		try {
			return event.getCommandExecutionStatus() == CL_COMPLETE;

		} catch (CLAL::CLException& e) {
			throw ExceptionCLImpl(e.what());
		}

	}

}
