
#ifndef _HQ_WORKER_HPP_
#define _HQ_WORKER_HPP_


#include <vector>
#include "ComputeUnit.hpp"
//#include "ThreadPool.hpp"

// for testing
#include <atomic>

namespace HQ {

	class ThreadPool;

	class Worker {

	public:
		// tmp
		//Worker() = delete; 
		//Worker(const Worker&) = delete;
		//Worker(Worker&&) = default;

		Worker(ThreadPool& pool);
		void operator ()();


		~Worker();

	private:
		
		ThreadPool& poolRef;

		std::vector<ComputeUnit*> computeUnits;
		int id;

	};

	// test
	static std::atomic<int> worker_count = 0;


}


#endif

