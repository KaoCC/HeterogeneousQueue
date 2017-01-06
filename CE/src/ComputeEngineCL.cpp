#include "ComputeEngineCL.hpp"
#include "ExceptionCLImpl.hpp"
#include "DeviceCLImpl.hpp"


namespace CE {





	ComputeEngineCL::ComputeEngineCL() {


		// KAOCC: chould we throw in the ctor?
		try {

			CLAL::CLPlatform::createAllPlatforms(platforms);

			// Get all devices on the platform
			for (auto const& platform : platforms) {
				size_t numOfDevices = platform.getDeviceCount();

				for (size_t i = 0; i < numOfDevices; ++i) {
					auto device = platform.getDevice(i);
					devices.push_back(device);
				}
			}

		} catch (CLAL::CLException& e) {
			throw ExceptionCLImpl(e.what());
		}

	}

	Device * ComputeEngineCL::createDevice(size_t index) {

		if (index >= devices.size()) {
			throw ExceptionCLImpl("Index Out Of Bounds");
		}

		try {
			return new DeviceCLImpl(devices[index]);

		} catch (CLAL::CLException& e) {
			throw ExceptionCLImpl(e.what());
		}
	}

	void ComputeEngineCL::deleteDevice(Device * device) {
		delete device;
	}


	size_t ComputeEngineCL::getDeviceCount() const {
		return devices.size();
	}





	PlatformType ComputeEngineCL::getPlatformType() const {
		return PlatformType::kOpenCL;
	}

}
