#ifndef _CLAL_CLPLATFORM_HPP_
#define _CLAL_CLPLATFORM_HPP_

#include "CLReferenceCount.hpp"
#include "CLDevice.hpp"

#include <vector>
#include <string>



namespace CLAL {

	// TODO : CLPlatfrom has no deleter !!!
	// need to customize the Reference counter
	class CLPlatform : public ReferenceCount<cl_platform_id, nullptr, nullptr> {

	public:

		//TODO: impl.
		static void CreateAllPlatforms(std::vector<CLPlatform>& platforms);


		const std::string& getName() const;
		const std::string& getProfile() const;
		const std::string& getVendor() const;



		size_t getDeviceCount() const;

		virtual ~CLPlatform();

	private:

		// TODO: make a universal template
		void getPlatformInfoWithParameter(cl_platform_id id, cl_platform_info param, std::string& result);


		// basic info of a platform
		std::string name;
		std::string profile;
		std::string version;
		std::string vendor;


		// store the device list
		std::vector<CLDevice> devices;
	};



}





#endif