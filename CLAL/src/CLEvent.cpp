#include "CLEvent.hpp"
#include "CLException.hpp"

namespace CLAL {

	CLEvent::CLEvent(cl_event event) :
		ReferenceCount<cl_event, clRetainEvent, clReleaseEvent>(event) {
	}

	// KAOCC: note: release it manually
	CLEvent CLEvent::create(cl_event evt) {
		CLEvent retEvent(evt);
		clReleaseEvent(evt);
		return retEvent;
	}

	//CLEvent::CLEvent() {
	//}

	void CLEvent::wait() {
		cl_event event = *this;
		cl_int status = clWaitForEvents(1, &event);
		ThrowIfCL(status != CL_SUCCESS, status, "clWaitForEvents failed");
	}


	// TODO: Yet to be done !
	float CLEvent::getDuration() const {
		return 0.0f;
	}

	cl_int CLEvent::getCommandExecutionStatus() const {

		cl_int cmdStatus;
		cl_int status = clGetEventInfo(*this, CL_EVENT_COMMAND_EXECUTION_STATUS, sizeof(cl_int), &cmdStatus, nullptr);
		ThrowIfCL(status != CL_SUCCESS, status, "clGetEventInfo failed");

		return cmdStatus;
	}

	CLEvent::~CLEvent() {
	}
}
