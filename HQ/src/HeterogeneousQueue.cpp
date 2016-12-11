#include "HeterogeneousQueue.hpp"



namespace HQ {

	HeterogeneousQueue::HeterogeneousQueue() : platform(), threadPool(platform) {
	}

	void HeterogeneousQueue::enqueue(Task * task) {
		threadPool.enqueue(task);
	}

	size_t HeterogeneousQueue::getNumberOfUnitOnPlatform() const {
		return platform.getNumberOfComputeUnit();
	}

	const ComputePlatform & HeterogeneousQueue::getPlatfrom() const {

		return platform;

	}

}
