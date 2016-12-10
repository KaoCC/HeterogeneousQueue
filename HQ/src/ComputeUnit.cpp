
#include "ComputeUnit.hpp"

#include "Device.hpp"


namespace HQ {


	ComputeUnit::ComputeUnit(CE::ComputeEngine* ce, size_t index) {
		// tmp
		device = ce->createDevice(index);

		CE::DeviceSpec spec;
		device->GetSpec(spec);
		if (spec.type == CE::DeviceType::kSequential) {
			
			// put it here or user space ?
			//CreateSequentialExecutable(device);
			

		}

	}

}


