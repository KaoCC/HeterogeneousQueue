
#include "ThreadPool.hpp"
#include "ComputePlatform.hpp"
#include "ComputeUnit.hpp"

#include "ComputeEngine.hpp"

namespace HQ {

	ComputePlatform::ComputePlatform() {

		// kMix for sequential & CL
		ce = CE::CreateComputeEngine(CE::kMix);

		// TODO: may need to change the ctor
		for (size_t i = 0; i < NUM_OF_UNITS; ++i) {
			computeUnits.push_back(new ComputeUnit(ce, i));
		}


	}


	void ComputePlatform::enqueue(Task * task) {

		// tmp
		// simple impl.

		size_t gs = task->getGlobalSize();
		size_t partial = gs / computeUnits.size();
		size_t sz = 0;

		for (size_t i = 0; i < computeUnits.size(); ++i) {

			if ((gs - partial) / partial > 0) {
				sz = partial;
			} else {
				sz = gs;
			}


			// TODO: need to set up the offset
			// TODO: need to be a thread pool model
			// TODO: sync ?
			computeUnits[i]->exeucte(task->getRunFunction(i), sz);

			gs -= partial;
		}


	}

	// should be removed
	ComputeUnit * ComputePlatform::getComputeUnit(size_t index) const {

		if (index < NUM_OF_UNITS) {
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
		for (size_t i = 0; i < NUM_OF_UNITS; ++i) {
			delete computeUnits[i];
		}

		CE::DeleteComputeEngine(ce);
	}

}


