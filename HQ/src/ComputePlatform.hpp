
#ifndef _HQ_COMPUTEPLATFORM_HPP_
#define _HQ_COMPUTEPLATFORM_HPP_


#include <vector>
#include "ComputeUnit.hpp"
//#include "ThreadPool.hpp"

// From CE
#include "ComputeEngine.hpp"

namespace HQ {



	class ComputePlatform {

	public:


		ComputePlatform();


		//TODO: add enqueue member function
		// param: Task ?
		//void enqueue();


		~ComputePlatform();

		ComputePlatform(const ComputePlatform&) = delete;
		ComputePlatform& operator=(const ComputePlatform&) = delete;
		ComputePlatform(ComputePlatform&&) = delete;

	private:


		// test
		static const size_t numberOfUnits = 1;

		std::vector<ComputeUnit*> computeUnits;

		
		CE::ComputeEngine* ce {nullptr};

	};



}


#endif

