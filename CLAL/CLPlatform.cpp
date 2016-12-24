

#include <functional>
#include <algorithm>
#include <iterator>

#include "CLPlatform.hpp"
#include "CLException.hpp"

namespace CLAL {


	CLPlatform CLPlatform::create(cl_platform_id id, cl_device_type type) {
		return CLPlatform(id);
	}


	//TODO: impl.
	void CLPlatform::createAllPlatforms(std::vector<CLPlatform>& platforms) {

		// CL status code
		cl_int status = CL_SUCCESS;

		// get number of platforms
		cl_uint numPlatforms;
		status = clGetPlatformIDs(0, nullptr, &numPlatforms);
		ThrowIfCL(status != CL_SUCCESS, status, "clGetPlatformIDs failed");

		// all platform IDs
		std::vector<cl_platform_id> platformIds(numPlatforms);
		// after filtering
		std::vector<cl_platform_id> validIds;

		// get everything
		status = clGetPlatformIDs(numPlatforms, platformIds.data(), nullptr);
		ThrowIfCL(status != CL_SUCCESS, status, "clGetPlatformIDs failed");

		
		platforms.clear();

		// do the filtering
		// we want only CL 1.2+ & Non-Intel Device
		for (size_t i = 0; i < platformIds.size(); ++i) {

			// take out stuffs that are below 1.2
			size_t size = 0;
			status = clGetPlatformInfo(platformIds[i], CL_PLATFORM_VERSION, 0, nullptr, &size);

			std::vector<char> version(size);
			status = clGetPlatformInfo(platformIds[i], CL_PLATFORM_VERSION, size, version.data(), 0);

			std::string versionstr(version.begin(), version.end());

			if (versionstr.find("1.0") != std::string::npos ||
				versionstr.find("1.1") != std::string::npos) {
				continue;
			}

			// check if it is an intel platform
			size = 0;
			status = clGetPlatformInfo(platformIds[i], CL_PLATFORM_VENDOR, 0, nullptr, &size);

			std::vector<char> vendor(size);
			status = clGetPlatformInfo(platformIds[i], CL_PLATFORM_VENDOR, size, vendor.data(), 0);

			std::string vendorstr(vendor.begin(), vendor.end());

			if (vendorstr.find("Intel") != std::string::npos) {
				continue;
			}

			validIds.push_back(platformIds[i]);

		}


		// store to platforms !
		std::transform(validIds.cbegin(), validIds.cend(), std::back_inserter(platforms),
			std::bind(&CLPlatform::Create, std::placeholders::_1, CL_DEVICE_TYPE_ALL));
	}


	const std::string & CLPlatform::getName() const {
		return name;
	}

	const std::string & CLPlatform::getProfile() const {
		return profile;
	}

	const std::string & CLPlatform::getVendor() const {
		return vendor;
	}


	CLDevice CLPlatform::getDevice(size_t index) const {
		// lazy init.
		if (devices.size() == 0) {
			initDeviceList(INIT_DEVICE_TYPE);
		}

		return devices[index];
	}

	size_t CLPlatform::getDeviceCount() const {

		// lazy init.
		if (devices.size() == 0) {
			initDeviceList(INIT_DEVICE_TYPE);
		}

		return devices.size();
	}

	CLPlatform::~CLPlatform() {
	}



	CLPlatform::CLPlatform(cl_platform_id platformId) : ReferenceCount<cl_platform_id, nullptr, nullptr>(platformId) {

		getPlatformInfoWithParameter(*this, CL_PLATFORM_NAME, name);
		getPlatformInfoWithParameter(*this, CL_PLATFORM_PROFILE, profile);
		getPlatformInfoWithParameter(*this, CL_PLATFORM_VERSION, version);
		getPlatformInfoWithParameter(*this, CL_PLATFORM_VENDOR, vendor);
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

	void CLPlatform::initDeviceList(cl_device_type type) const {

		cl_uint numDevices = 0;

		// get number of devices
		cl_int status = clGetDeviceIDs(*this, type, 0, nullptr, &numDevices);
		ThrowIfCL(status != CL_SUCCESS, status, "clGetDeviceIDs failed");

		std::vector<cl_device_id> deviceIds(numDevices);

		// get device info
		status = clGetDeviceIDs(*this, type, numDevices, deviceIds.data(), nullptr);
		ThrowIfCL(status != CL_SUCCESS, status, "clGetDeviceIDs failed");


		// store the device list
		for (cl_uint i = 0; i < numDevices; ++i) {
			devices.push_back(CLDevice::Create(deviceIds[i]));
		}

	}


}