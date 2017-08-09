
#include "ComputeEngineMix.hpp"
#include "ExceptionCLImpl.hpp"

#include "DeviceSequential.hpp"
#include "DeviceCLImpl.hpp"

#include <iostream>

namespace CE {

	ComputeEngineMix::ComputeEngineMix() : numberOfDeviceInEngine(0) {
		
		// KAOCC: should we throw in ctor ?

		// The OpenCL Part
		try {

			CLAL::CLPlatform::createAllPlatforms(platforms);

			// Get all GPU devices on the platform, filter out the CPUs
			for (auto const& platform : platforms) {
				size_t numOfDevices = platform.getDeviceCount();

				std::cerr << "Platform: " << platform.getName() << platform.getVendor() << platform.getProfile() << std::endl;

				for (size_t i = 0; i < numOfDevices; ++i) {
					auto device = platform.getDevice(i);

					std::cerr << "Device:" << device.getName() << device.getVendor() << device.getType() << device.getVersion() << std::endl;

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
		
		std::cerr << "device count: " << numberOfDeviceInEngine << std::endl;

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
			throw std::runtime_error("Number of device exceeds");
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
