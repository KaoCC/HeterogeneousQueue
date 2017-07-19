
#ifndef _HQ_HETEROGENEOUSQUEUE_HPP_
#define _HQ_HETEROGENEOUSQUEUE_HPP_


#include "ThreadPool.hpp"
#include "ComputePlatform.hpp"

namespace HQ {

	class Task;

	class HeterogeneousQueue {

	public:
		HeterogeneousQueue();

		~HeterogeneousQueue();
		
		void enqueue(Task* task);
		size_t getNumberOfUnitOnPlatform() const;


		// tmp
		const ComputePlatform& getPlatfrom() const;

	private:

		// enqueue helper function
		// remove ?
		static void submitTask(ComputePlatform& platform, Task* task);

		ComputePlatform mPlatform;
		//ThreadPool<void> threadPool;


		// ---- new design

		void runLoop(ComputeUnit& cu);

		// check for the lock
		// atomic ?
		std::atomic_bool terminated{ false };

		std::vector<std::thread> mWorkerThreads;

		// task Queue
		ThreadSafeQueue<Task*> mTaskQueue;


	};



}




#endif
