
#ifndef _HQ_HETEROGENEOUSQUEUE_HPP_
#define _HQ_HETEROGENEOUSQUEUE_HPP_


#include "ThreadPool.hpp"

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
		ComputePlatform platform;
		ThreadPool threadPool;
	};



}




#endif
