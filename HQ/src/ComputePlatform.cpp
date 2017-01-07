
#include "ThreadPool.hpp"
#include "ComputePlatform.hpp"
#include "ComputeUnit.hpp"

#include "ComputeEngine.hpp"

#include <thread>
#include <array>

namespace HQ {

	ComputePlatform::ComputePlatform() {

		// kMix for sequential & CL
		ce = CE::CreateComputeEngine(CE::kMix);

		// TODO: may need to change the ctor
		// Thread ?

		// tmp solution

		size_t deviceCount = ce->getDeviceCount();

		for (size_t i = 0; i < deviceCount; ++i) {
			computeUnits.push_back(new ComputeUnit(ce, i));
		}


	}


	void ComputePlatform::enqueue(Task * task) {

		// tmp
		// simple impl.


		// clear
		futures.clear();  // is this thread safe ???

		size_t gs = task->getGlobalSize();
		const size_t partial = gs / computeUnits.size();


		size_t sz = partial;
		for (size_t i = 0; i < computeUnits.size(); ++i) {

			if (i == computeUnits.size() - 1) {
				// add the rest
				sz += gs - (partial * computeUnits.size());
			}


			// TODO: need to set up the offset
			// TODO: need to be a thread pool model
			// TODO: sync ?
			// KAOCC: Offset ???
			futures.push_back(std::async(dispatch, computeUnits[i], task->getRunFunction(i), sz, partial * i));
		}

		for (auto& f : futures) {
			f.get();
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
	//TODO: we may return Event later on
	void ComputePlatform::dispatch(ComputeUnit * cu, CE::Function const* func, size_t globalSz, size_t offset) {

		// tmp
		cu->submit(func, globalSz);
	}

}


