#ifndef _CLAL_CLDEVICE_HPP_
#define _CLAL_CLDEVICE_HPP_

#include "CLReferenceCount.hpp"

#include <string>

namespace CLAL {


	class CLDevice : public ReferenceCount<cl_device_id, clRetainDevice, clReleaseDevice> {


	public:

		CLDevice();

		// wrap cl_device_id
		CLDevice(cl_device_id id);
		

		std::string const& GetName() const;
		std::string const& GetVendor() const;
		std::string const& GetVersion() const;

		virtual ~CLDevice();

	private:
		std::string name;
		std::string vendor;
		std::string version;

	};


}






#endif
