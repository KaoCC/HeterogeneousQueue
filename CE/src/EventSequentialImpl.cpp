#include "EventSequentialImpl.hpp"


namespace CE {

	EventSequentialImpl::EventSequentialImpl(std::future<void>& fu) : mFuture{std::move(fu)} {
	}

	void EventSequentialImpl::wait() {
		mFuture.wait();
	}

	// need check
	bool EventSequentialImpl::isComplete() const {
		return false;
	}


}