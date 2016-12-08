
#include "ComputeUnit.hpp"




namespace HQ {


	ComputeUnit::ComputeUnit(CE::ComputeEngine* ce, size_t index) {
		device = ce->createDevice(index);
	}

}


