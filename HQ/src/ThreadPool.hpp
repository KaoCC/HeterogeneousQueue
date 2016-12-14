

#ifndef _THREADPOOL_H_
#define _THREADPOOL_H_

#include <condition_variable>
#include <atomic>
#include <mutex>
#include <thread>
#include <queue>
#include <future>
#include <algorithm>

#include "ThreadSafeQueue.hpp"

namespace HQ {

	
	class ThreadPool {

	public:

		ThreadPool();
		
		void enqueue(std::function<void()>&& f);
		size_t getSize() const;

		const std::atomic_bool& isDone() const;

		~ThreadPool();

		const int sleepTime = 20;

	private:

		void runLoop();

		std::atomic_bool done{ false };
		std::vector<std::thread> workerThreads;

		ThreadSafeQueue<std::packaged_task<void()>> taskQueue;

	};

}




#endif







