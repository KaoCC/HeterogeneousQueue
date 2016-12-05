

#ifndef _THREADPOOL_H_
#define _THREADPOOL_H_

#include <condition_variable>
#include <atomic>
#include <mutex>
#include <thread>
#include <queue>
#include <future>
#include <algorithm>


#include "HQ.hpp"
#include "ThreadSafeQueue.hpp"

namespace HQ {


	class ThreadPool {

	public:

		ThreadPool();
		
		void enqueue(Task* task);
		size_t getSize() const;

		~ThreadPool();


	private:

		void runLoop();

		int sleepTime = 20;
		std::atomic_bool done{ false };
		std::vector<std::thread> workerThreads;
		ThreadSafeQueue<Task*> taskQueue;

	};

}




#endif







