#include "CLDevice.hpp"
#include <vector>

namespace CLAL {

	// static function for Named Constructor Idiom & Factory Model
	CLDevice CLDevice::Create(cl_device_id id) {
		return CLDevice(id);
	}


	CLDevice::CLDevice() {
	}



	// wrap cl_device_id
	CLDevice::CLDevice(cl_device_id deviceID) : ReferenceCount<cl_device_id, clRetainDevice, clReleaseDevice>(deviceID) {
		//TODO: more here !!!


		getDeviceInfoWithParameter(*this, CL_DEVICE_NAME, name);
		getDeviceInfoWithParameter(*this, CL_DEVICE_VENDOR, vendor);
		getDeviceInfoWithParameter(*this, CL_DEVICE_VERSION, version);
		// ...
		getDeviceInfoWithParameter(*this, CL_DEVICE_TYPE, type);
		// ...

	}


	CLDevice::~CLDevice() {
	}

	const std::string& CLDevice::getName() const {
		return name;
	}

	const std::string& CLDevice::getVendor() const {
		return vendor;
	}

	const std::string& CLDevice::getVersion() const {
		return version;
	}

	cl_device_type CLDevice::getType() const {
		return type;
	}

	cl_device_id CLDevice::getID() const {
		return *this;
	}







	// for std::string
	template <>
	void CLDevice::getDeviceInfoWithParameter<std::string>(cl_device_id id, cl_device_info param, std::string& value) {

		size_t length = 0;

		// get length
		cl_int status = clGetDeviceInfo(id, param, 0, nullptr, &length);
		ThrowIfCL(status != CL_SUCCESS, status, "clGetDeviceInfo failed");

		// init buffer (perhpas we can use the reference directly ?)
		std::vector<char> buffer(length);
		clGetDeviceInfo(id, param, length, buffer.data(), nullptr);
		ThrowIfCL(status != CL_SUCCESS, status, "clGetDeviceInfo failed");

		value = buffer.data();
	}


}