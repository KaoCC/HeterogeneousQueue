
#ifndef _HQ_HETEROGENEOUSQUEUE_HPP_
#define _HQ_HETEROGENEOUSQUEUE_HPP_


#include "ThreadPool.hpp"
#include "ComputePlatform.hpp"

namespace HQ {

	class Task;

	class HeterogeneousQueue {

	public:
		HeterogeneousQueue();
		
		void enqueue(Task* task);
		size_t getNumberOfUnitOnPlatform() const;


		// tmp
		const ComputePlatform& getPlatfrom() const;

	private:

		// enqueue helper function
		static void submitTask(ComputePlatform& platform, Task* task);

		ComputePlatform platform;
		ThreadPool<void> threadPool;
	};



}




#endif
