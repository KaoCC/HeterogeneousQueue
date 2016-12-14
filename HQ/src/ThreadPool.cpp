
#include "ComputePlatform.hpp"
#include "ThreadPool.hpp"

#include <functional>

namespace HQ {


	ThreadPool::ThreadPool() {

		unsigned numberOfThreads = std::thread::hardware_concurrency();
		if (!numberOfThreads) {
			numberOfThreads = 4;
		}

		// test
		//std::cerr << numberOfThreads << std::endl;

		for (size_t i = 0; i < numberOfThreads; ++i) {
			workerThreads.push_back(std::thread(&ThreadPool::runLoop, this));
		}

	}

	//void ThreadPool::enqueue(Task* task) {

	//	//TODO: may need to add something related to Event...
	//	taskQueue.push(task);

	//}


	void ThreadPool::enqueue(std::function<void()>&& f) {

		std::packaged_task<void()> task { std::move(f) };
		taskQueue.push(std::move(task));
	}

	size_t ThreadPool::getSize() const {
		return taskQueue.size();
	}


	const std::atomic_bool& ThreadPool::isDone() const {
		return done;
	}


	void ThreadPool::runLoop() {

		//Task* task = nullptr;

		std::packaged_task<void()> runFunction;

		while (!done) {

			if (taskQueue.pop(runFunction)) {

				//auto& runFunction = task->getRunFunction();
				//runFunction(task->getTaskParameter());

				//platformRef.enqueue(task);

				//TODO: check for event ?

				//Event* event = task->getEvent();
				//if (event) {
				//	event->signal();
				//}

				runFunction();

			} else {
				std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
			}

		}

	}

	ThreadPool::~ThreadPool() {
		done = true;
		std::for_each(workerThreads.begin(), workerThreads.end(), std::mem_fun_ref(&std::thread::join));
	}


}












