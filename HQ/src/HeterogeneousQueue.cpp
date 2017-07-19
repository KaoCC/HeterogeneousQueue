#include "HeterogeneousQueue.hpp"

#include <functional>


namespace HQ {
	
	HeterogeneousQueue::HeterogeneousQueue() : mPlatform{} {


		std::size_t numOfCUs{ mPlatform.getNumberOfComputeUnit() };

		for (std::size_t i = 0; i < numOfCUs; ++i) {
			mWorkerThreads.push_back(std::thread(&HeterogeneousQueue::runLoop, this, std::ref(mPlatform.getComputeUnit(i))));
		}
	}

	HeterogeneousQueue::~HeterogeneousQueue() {

		terminated = true;

		// thread cleanup
		std::for_each(mWorkerThreads.begin(), mWorkerThreads.end(), std::mem_fun_ref(&std::thread::join));
	}

	void HeterogeneousQueue::enqueue(Task * task) {
		//auto f = std::bind(&HeterogeneousQueue::submitTask, std::ref(platform), task );
		//threadPool.enqueue(std::move(f));


		mTaskQueue.push(task);

	}

	size_t HeterogeneousQueue::getNumberOfUnitOnPlatform() const {
		return mPlatform.getNumberOfComputeUnit();
	}

	const ComputePlatform & HeterogeneousQueue::getPlatfrom() const {

		return mPlatform;
	}


	// helper function
	void HeterogeneousQueue::submitTask(ComputePlatform& platform, Task * task) {


		// more here !

		//platform.enqueue(task);

		//// Need to change the Event system
		//Event* event = task->getEvent();
		//if (event) {
		//	event->signal();
		//}
	}

	void HeterogeneousQueue::runLoop(ComputeUnit & cu) {

		Task* task;
		while (!terminated) {

			// yet to be done 

			mTaskQueue.popWait(task);
			cu.execute(task);
		}

	}

}

