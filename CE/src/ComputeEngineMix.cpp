
#include "ComputeEngineMix.hpp"
#include "ExceptionCLImpl.hpp"

#include "DeviceSequential.hpp"
#include "DeviceCLImpl.hpp"

namespace CE {

	ComputeEngineMix::ComputeEngineMix() : numberOfDeviceInEngine(0) {
		
		// KAOCC: should we throw in ctor ?

		// The OpenCL Part
		try {

			CLAL::CLPlatform::createAllPlatforms(platforms);

			// Get all GPU devices on the platform, filter out the CPUs
			for (auto const& platform : platforms) {
				size_t numOfDevices = platform.getDeviceCount();

				for (size_t i = 0; i < numOfDevices; ++i) {
					auto device = platform.getDevice(i);

					// Take out CPUs
					if (device.getType() != CL_DEVICE_TYPE_CPU) {
						devices.push_back(device);
						++(this->numberOfDeviceInEngine);
					}
				}
			}

		} catch (CLAL::CLException& e) {
			throw ExceptionCLImpl(e.what());
		}


		// plus one for CPU Sequential Device
		numberOfDeviceInEngine += 1;
		

	}

	size_t ComputeEngineMix::getDeviceCount() const {
		return numberOfDeviceInEngine;
	}

	PlatformType ComputeEngineMix::getPlatformType() const {
		return PlatformType::kMix;
	}

	Device* ComputeEngineMix::createDevice(size_t index) {
		//FIXME: yet to be done
	
		if (index >= numberOfDeviceInEngine) {
			throw "Number of device exceeds";
		}

		
		// the first one is the sequential device
		if (index == 0) {
			// CPU
			return new DeviceSequential();
		} else {
			// GPU
			return new DeviceCLImpl(devices[index - 1]);
		}


	}

	void ComputeEngineMix::deleteDevice(Device * device) {

		delete device;
	}


}