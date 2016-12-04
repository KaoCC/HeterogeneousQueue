

#include "EventSys.hpp"


namespace HQ {

	EventSys::EventSys(unsigned long c) : count(c) {

	}


	void EventSys::wait() {

		std::unique_lock<std::mutex> lock(localMutex);

		while (count == 0) {
			localCondition.wait(lock);
		}

		--count;

	}


	void EventSys::signal() {
		std::unique_lock<std::mutex> lock(localMutex);

		++count;
		localCondition.notify_one();

	}


	bool EventSys::isComplete() const {
		throw "not yet supported";
	}



	Event* hqCreateEvent() {
		return new EventSys();
	}

	void hqDestroyEvent(Event* event) {
		if (event) {
			delete event;
		}
	}

}
