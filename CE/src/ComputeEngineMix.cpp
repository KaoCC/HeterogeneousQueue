
#include "ComputeEngineMix.hpp"


#include "DeviceSequential.hpp"


namespace CE {

	ComputeEngineMix::ComputeEngineMix() {
		// init devices ?
	}

	size_t ComputeEngineMix::getDeviceCount() const {
		// test
		return NUM_OF_DEVICE;
	}

	Platform ComputeEngineMix::getPlatform() const {
		return Platform::kMix;
	}

	Device* ComputeEngineMix::createDevice(size_t index) {
		//FIXME: yet to be done
	
		if (index >= NUM_OF_DEVICE) {
			throw "Number of device exceeds";
		}

		
		// the first one is the sequential device
		if (index == 0) {
			deviceList[index] = new DeviceSequential();
		}

		return deviceList[index];



	}

	void ComputeEngineMix::deleteDevice(Device * device) {

		// need to change
		if (device) {
			delete device;
		}
	}


}