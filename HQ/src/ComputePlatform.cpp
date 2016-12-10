
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



	ComputeUnit * ComputePlatform::getComputeUnit(size_t index) {

		if (index < NUM_OF_UNITS) {
			return computeUnits[index];
		} else {
			// throw ?
			return nullptr;
		}
	}


	ComputePlatform::~ComputePlatform() {
		for (size_t i = 0; i < NUM_OF_UNITS; ++i) {
			delete computeUnits[i];
		}

		CE::DeleteComputeEngine(ce);
	}

}


