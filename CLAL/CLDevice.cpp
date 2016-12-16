#include "CLDevice.hpp"

namespace CLAL {

	CLDevice::CLDevice() {
	}

	// wrap cl_device_id
	CLDevice::CLDevice(cl_device_id deviceID) : ReferenceCount<cl_device_id, clRetainDevice, clReleaseDevice>(deviceID) {
		//TODO: more here !!!
	}

	CLDevice::~CLDevice() {
	}

	std::string const & CLDevice::GetName() const {
		return name;
	}

	std::string const & CLDevice::GetVendor() const {
		return vendor;
	}

	std::string const & CLDevice::GetVersion() const {
		return version;
	}


}