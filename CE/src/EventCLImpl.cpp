#include "EventCLImpl.hpp"
#include "ExceptionCLImpl.hpp"
#include "CLEvent.hpp"
#include "CLException.hpp"

namespace CE {
	EventCLImpl::EventCLImpl() {

	}

	EventCLImpl::~EventCLImpl() {
	}

	void EventCLImpl::wait() {

		try {

			if (validFlag) {
				event.wait();
			} else {
				throw "invald event ID";
			}

		} catch (CLAL::CLException& e) {
			throw ExceptionCLImpl(e.what());
		}
	}


	bool EventCLImpl::isComplete() const {


		try {

			if (validFlag) {
				return event.getCommandExecutionStatus() == CL_COMPLETE;
			} else {
				throw "invald event ID";
			}

		} catch (CLAL::CLException& e) {
			throw ExceptionCLImpl(e.what());
		}

	}

	void EventCLImpl::setEvent(CLAL::CLEvent evt) {
		this->event = evt;
		validFlag = true;
	}

}
