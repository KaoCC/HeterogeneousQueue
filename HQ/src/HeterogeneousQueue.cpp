#include "HeterogeneousQueue.hpp"

#include <functional>


namespace HQ {
	
	HeterogeneousQueue::HeterogeneousQueue() {
	}

	void HeterogeneousQueue::enqueue(Task * task) {
		auto f = std::bind(&HeterogeneousQueue::submitTask, std::ref(platform), task );
		threadPool.enqueue(std::move(f));
	}

	size_t HeterogeneousQueue::getNumberOfUnitOnPlatform() const {
		return platform.getNumberOfComputeUnit();
	}

	const ComputePlatform & HeterogeneousQueue::getPlatfrom() const {

		return platform;

	}


	// helper function
	void HeterogeneousQueue::submitTask(ComputePlatform& platform, Task * task) {

		platform.enqueue(task);

		Event* event = task->getEvent();
		if (event) {
			event->signal();
		}
	}

}

