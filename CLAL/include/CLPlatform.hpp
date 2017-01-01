#ifndef _CLAL_CLPLATFORM_HPP_
#define _CLAL_CLPLATFORM_HPP_

#include "CLReferenceCount.hpp"
#include "CLDevice.hpp"

#include <vector>
#include <string>



namespace CLAL {

	class CLPlatform : public ReferenceCount<cl_platform_id, nullptr, nullptr> {

	public:

		// KAOCC: type is not used at the current impl.
		static CLPlatform create(cl_platform_id id, cl_device_type type = CL_DEVICE_TYPE_ALL);

		static void createAllPlatforms(std::vector<CLPlatform>& platforms);


		CLPlatform() = delete;

		const std::string& getName() const;
		const std::string& getProfile() const;
		const std::string& getVendor() const;



		CLDevice getDevice(size_t index) const;
		size_t getDeviceCount() const;


		virtual ~CLPlatform();

	private:

		// wrapper
		CLPlatform(cl_platform_id id);

		// TODO: make a universal template
		void getPlatformInfoWithParameter(cl_platform_id id, cl_platform_info param, std::string& result);
		void initDeviceList(cl_device_type type) const;

		// basic info of a platform
		std::string name;
		std::string profile;
		std::string version;
		std::string vendor;


		// store the device list
		//must be mutable since we used it from const member functions
		mutable std::vector<CLDevice> devices;

		// by default, we use all devices
		// tmp Impl.
		const cl_device_type INIT_DEVICE_TYPE = CL_DEVICE_TYPE_ALL;
	};



}





#endif