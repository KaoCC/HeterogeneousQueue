
#include "ComputePlatform.hpp"
#include "ThreadPool.hpp"

#include <iostream>

namespace HQ {


	ThreadPool::ThreadPool() {

		unsigned numberOfThreads = std::thread::hardware_concurrency();
		if (!numberOfThreads) {
			numberOfThreads = 4;
		}

		// test
		std::cerr << numberOfThreads << std::endl;

		for (size_t i = 0; i < numberOfThreads; ++i) {
			workerThreads.push_back(std::thread(&ThreadPool::runLoop, this));
		}

	}

	void ThreadPool::enqueue(Task* task) {

		//TODO: may need to add something related to Event...
		taskQueue.push(task);

	}


	size_t ThreadPool::getSize() const {
		return taskQueue.size();
	}


	const std::atomic_bool& ThreadPool::isDone() const {
		return done;
	}


	void ThreadPool::runLoop() {

		// init the ComputePlatform
		//ComputePlatform w;

		Task* task = nullptr;

		while (!done) {

			if (taskQueue.pop(task)) {

				auto& runFunction = task->getRunFunction();
				runFunction(task->getTaskParameter());

				//TODO: check for event ?

				Event* event = task->getEvent();
				if (event) {
					event->signal();
				}


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












