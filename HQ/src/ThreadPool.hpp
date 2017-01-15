

#ifndef _HQ_THREADPOOL_H_
#define _HQ_THREADPOOL_H_

#include <condition_variable>
#include <atomic>
#include <mutex>
#include <thread>
#include <queue>
#include <future>
#include <algorithm>

#include "ThreadSafeQueue.hpp"

namespace HQ {

	template <typename ReturnType>
	class ThreadPool {

	public:

		ThreadPool(unsigned numberOfThreads = 0) {
			if (numberOfThreads != 0) {
				numberOfThreads = std::thread::hardware_concurrency();
			}

			if (!numberOfThreads) {
				numberOfThreads = 4;
			}

			// test
			//std::cerr << numberOfThreads << std::endl;

			for (size_t i = 0; i < numberOfThreads; ++i) {
				workerThreads.push_back(std::thread(&ThreadPool::runLoop, this));
			}
		}
		
		std::future<ReturnType> enqueue(std::function<ReturnType()>&& f) {
			std::packaged_task<ReturnType()> task{ std::move(f) };
			auto taskFuture = task.get_future();
			taskQueue.push(std::move(task));

			return taskFuture;
		}


		size_t getSize() const {
			return taskQueue.size();
		}

		const std::atomic_bool& isDone() const {
			return done;
		}

		~ThreadPool() {
			done = true;
			std::for_each(workerThreads.begin(), workerThreads.end(), std::mem_fun_ref(&std::thread::join));
		}

		const int sleepTime = 10;

	private:

		void runLoop() {
			std::packaged_task<ReturnType()> runFunction;

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

		std::atomic_bool done{ false };
		std::vector<std::thread> workerThreads;

		ThreadSafeQueue<std::packaged_task<ReturnType()>> taskQueue;

	};

}




#endif







