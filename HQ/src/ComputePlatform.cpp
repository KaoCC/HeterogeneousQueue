
#include "ThreadPool.hpp"
#include "ComputePlatform.hpp"
#include "ComputeUnit.hpp"

#include "ComputeEngine.hpp"


#include "Event.hpp"

#include <thread>
#include <array>

// for testing
#include <iostream>

namespace HQ {

	ComputePlatform::ComputePlatform() : 
		ce (CE::CreateComputeEngine(CE::kMix)) {

		// kMix for sequential & CL
		//ce = CE::CreateComputeEngine(CE::kMix);

		// TODO: may need to change the ctor
		// Thread ?

		// tmp solution

		size_t deviceCount = ce->getDeviceCount();

		for (size_t i = 0; i < deviceCount; ++i) {
			computeUnits.push_back(new ComputeUnit(ce, i));
		}


		std::cerr << "Number of CUs:" << deviceCount << std::endl;
	}

	// NOTE: multi-thread
	void ComputePlatform::enqueue(Task * task) {

		// tmp
		// simple impl.


		// clear
		//std::vector<std::future<void>> futures; 

		//size_t gs = task->getGlobalSize();
		//const size_t partial = gs / computeUnits.size();


		//size_t sz = partial;
		//for (size_t i = 0; i < computeUnits.size(); ++i) {

		//	if (i == computeUnits.size() - 1) {
		//		// add the rest
		//		sz += gs - (partial * computeUnits.size());
		//	}


		//	// TODO: need to set up the offset
		//	// TODO: need to be a thread pool model
		//	// TODO: sync ?
		//	// KAOCC: Offset ???

		//	std::cerr << "Size: " << sz << std::endl;
		//	futures.push_back(std::async(dispatch, computeUnits[i], task->getRunFunction(i), sz, partial * i));
		//}

		//for (auto& f : futures) {
		//	f.get();
		//}


		// we will first implement a very simple dispatching algorithm to demo the effectiveness



		//NOTE: MAKE SURE EVERYTHING HERE CAN BE EXECUTED IN PARALLEL !!!!!!!

		// get a CU (index);
		// temp !!!
		int index = 1;

		// get the device from CU

		CE::Device* dev = computeUnits[index]->getDevice();

		// get the function from task

		CE::Function* func = task->getRunFunction(index);


		// get number of parameters

		size_t numOfParams = task->getNumOfParameters();

		// records for buffers

		std::vector<CE::Buffer*> buffers(numOfParams);

		for (size_t i = 0; i < numOfParams; ++i) {

			// get Task parameters from the task

			TaskParameter* taskParam = task->getTaskParameter(i);

			// create buffers based on the parameters

			// KAOCC: flag is not used
			buffers[i] = dev->createBuffer(taskParam->getSizeInByte(), 0, taskParam->getData());

			// copy buffers (kernel set Args ?)

			// Seems like we dont need to write ?
			//dev->writeBuffer();

			// kernel set Args 
			func->setArg(i, buffers[i]);
		}


		// Setup Event ?


		// dispatch the task
		
		// KAOCC: The design of the event system is wrong !

		CE::Event* evt = nullptr;

		// This will be wrong: The issue caused by Event System
		//computeUnits[index]->submit(func, task->getGlobalSize(), &evt);

		// tmp
		const size_t LOCAL_SZ = 64;
		dev->execute(func, 0, task->getGlobalSize(), LOCAL_SZ, &evt);

		// when done...

		evt->wait();

		// copy the buffer back to host

		for (size_t i = 0; i < numOfParams; ++i) {

			TaskParameter* taskParam = task->getTaskParameter(i);

			// KAOCC: Queue index is always 0 in the current impl.
			// KAOCC: Event is set to nullptr
			dev->readBuffer(buffers[i], 0, 0, taskParam->getSizeInByte(), taskParam->getData(), nullptr);

		}


		// relese event

		// ???


		// destroy buffers

		// ???

		for (size_t i = 0; i < numOfParams; ++i) {
			dev->deleteBuffer(buffers[i]);
		}

	}

	// should be removed
	ComputeUnit * ComputePlatform::getComputeUnit(size_t index) const {

		if (index < computeUnits.size()) {
			return computeUnits[index];
		} else {
			// throw ?
			return nullptr;
		}
	}


	size_t ComputePlatform::getNumberOfComputeUnit() const {
		return computeUnits.size();
	}


	ComputePlatform::~ComputePlatform() {
		for (size_t i = 0; i < computeUnits.size(); ++i) {
			delete computeUnits[i];
		}

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


