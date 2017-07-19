
#include "ThreadPool.hpp"
#include "ComputePlatform.hpp"
#include "ComputeUnit.hpp"

#include "ComputeEngine.hpp"


#include "Event.hpp"

#include <thread>
//#include <array>

// for testing
//#include <iostream>

namespace HQ {

	ComputePlatform::ComputePlatform() : 
		ce{ CE::CreateComputeEngine(CE::kMix) } {

		// kMix for sequential & CL
		//ce = CE::CreateComputeEngine(CE::kMix);

		// TODO: may need to change the ctor
		// Thread ?

		// tmp solution

		size_t deviceCount{ ce->getDeviceCount() };

		computeUnits.resize(deviceCount);
		for (size_t i = 0; i < deviceCount; ++i) {
			computeUnits[i] = std::make_unique<ComputeUnit>(ce, i);
		}


		//std::cerr << "Number of CUs:" << deviceCount << std::endl;
	}

	//// NOTE: multi-thread
	//void ComputePlatform::enqueue(Task * task) {


	//	// we will first implement a very simple dispatching algorithm to demo the effectiveness

	//	//NOTE: MAKE SURE EVERYTHING HERE CAN BE EXECUTED IN PARALLEL !!!!!!!
	//	// ex: Createbuffer, Read, Write, Exec with CL Queue

	//	// get a CU (index);
	//	// temp !!!
	//	// NOTE: index = 1 for GPU on CL
	//	int index = 1;
	//
	//	//std::future<CE::Event*> eventConsumer = computeUnits[index]->submit(task);

	//}


	// need to change
	ComputeUnit& ComputePlatform::getComputeUnit(size_t index) {

		return *computeUnits[index];
	}

	const ComputeUnit & ComputePlatform::getComputeUnit(size_t index) const {
		return *computeUnits[index];
	}


	size_t ComputePlatform::getNumberOfComputeUnit() const {
		return computeUnits.size();
	}


	ComputePlatform::~ComputePlatform() {

		CE::DeleteComputeEngine(ce);
	}


	// helper function
	// TODO: we may return Event later on
	// perhaps we don't need this anymore
	//void ComputePlatform::dispatch(ComputeUnit * cu, CE::Function const* func, size_t globalSz, size_t offset) {


	//	// copy buffer?


	//	// tmp
	//	// KAOCC: offset ?
	//	cu->submit(func, globalSz);


	//	// event ?

	//	// copy to host ?


	//	// cleanup or update state

	//}

}


