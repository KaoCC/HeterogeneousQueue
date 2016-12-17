#include "CLDevice.hpp"

namespace CLAL {

	CLDevice::CLDevice() {
	}



	// wrap cl_device_id
	CLDevice::CLDevice(cl_device_id deviceID) : ReferenceCount<cl_device_id, clRetainDevice, clReleaseDevice>(deviceID) {
		//TODO: more here !!!


		// ...
		getDeviceInfoWithParameter(*this, CL_DEVICE_TYPE, type);
		// ...

	}

	CLDevice::~CLDevice() {
	}

	std::string const & CLDevice::getName() const {
		return name;
	}

	std::string const & CLDevice::getVendor() const {
		return vendor;
	}

	std::string const & CLDevice::getVersion() const {
		return version;
	}

	cl_device_type CLDevice::getType() const {
		return type;
	}

	cl_device_id CLDevice::getID() const {
		return *this;
	}


}