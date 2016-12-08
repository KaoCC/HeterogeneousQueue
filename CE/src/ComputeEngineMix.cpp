
#include "ComputeEngineMix.hpp"





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

	Device* ComputeEngineMix::createDevice(size_t index) const {
		//FIXME: yet to be done
		return nullptr;
	}

	void ComputeEngineMix::deleteDevice(Device * device) {

		if (device) {
			delete device;
		}
	}


}