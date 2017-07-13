

#include "EventSys.hpp"


namespace HQ {

	EventSys::EventSys(unsigned long c) : count(c) {

	}


	void EventSys::wait() {

		std::unique_lock<std::mutex> lock(localMutex);


		localCondition.wait(lock, [this] {return count == 0; });

		--count;
	}


	void EventSys::signal() {
		std::unique_lock<std::mutex> lock(localMutex);

		++count;
		localCondition.notify_one();

	}


	bool EventSys::isComplete() const {
		throw std::runtime_error("not yet supported");
	}



	Event* CreateEvent() {
		return new EventSys();
	}

	void DestroyEvent(Event* event) {
		if (event) {
			delete event;
		}
	}

}
