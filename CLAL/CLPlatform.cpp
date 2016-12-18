#include "CLPlatform.hpp"


namespace CLAL {

	const std::string & CLPlatform::getName() const {
		return name;
	}

	const std::string & CLPlatform::getProfile() const {
		return profile;
	}

	const std::string & CLPlatform::getVendor() const {
		return vendor;
	}

	size_t CLPlatform::getDeviceCount() const {
		return devices.size();
	}

	CLPlatform::~CLPlatform() {
	}

	void CLPlatform::getPlatformInfoWithParameter(cl_platform_id id, cl_platform_info param, std::string & result) {

		size_t length = 0;

		// get length
		cl_int status = clGetPlatformInfo(id, param, 0, nullptr, &length);
		ThrowIfCL(status != CL_SUCCESS, status, "clGetPlatformInfo failed");

		// init buffer
		std::vector<char> buffer(length);
		status = clGetPlatformInfo(id, param, length, buffer.data(), nullptr);
		ThrowIfCL(status != CL_SUCCESS, status, "clGetPlatformInfo failed");

		result = buffer.data();
	}


}