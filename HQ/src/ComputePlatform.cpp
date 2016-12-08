
#include "ThreadPool.hpp"
#include "ComputePlatform.hpp"
#include "ComputeUnit.hpp"

#include "ComputeEngine.hpp"

namespace HQ {

	ComputePlatform::ComputePlatform() {

		// kMix for sequential & CL
		ce = CE::CreateComputeEngine(CE::kMix);

		// TODO: may need to change the ctor
		for (size_t i = 0; i < numberOfUnits; ++i) {
			computeUnits.push_back(new ComputeUnit(ce, i));
		}


	}



	ComputePlatform::~ComputePlatform() {
		for (size_t i = 0; i < numberOfUnits; ++i) {
			delete computeUnits[i];
		}

		CE::DeleteComputeEngine(ce);
	}

}


