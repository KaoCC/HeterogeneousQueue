#ifndef _CLAL_CLDEVICE_HPP_
#define _CLAL_CLDEVICE_HPP_

#include "CLReferenceCount.hpp"
#include "CLException.hpp"

#include <string>

namespace CLAL {


	class CLDevice : public ReferenceCount<cl_device_id, clRetainDevice, clReleaseDevice> {


	public:

		CLDevice();

		

		std::string const& getName() const;
		std::string const& getVendor() const;
		std::string const& getVersion() const;


		cl_device_type getType() const;


		cl_device_id getID() const;


		virtual ~CLDevice();

	private:

		// wrap cl_device_id
		CLDevice(cl_device_id id);

		template <typename T>
		void getDeviceInfoWithParameter(cl_device_id id, cl_device_info param, T& value);


		// CL info

		// strings need to be handled in a differnet way
		std::string name;
		std::string vendor;
		std::string version;



		// CL primitive types
		cl_device_type type;
		cl_ulong localMemSize;
		cl_ulong globalMemSize;
		cl_ulong maxAllocSize;
		cl_device_local_mem_type localMemType;
		size_t maxWorkGroupSize;
		cl_uint minAlignSize;
	};


	template <typename T>
	void CLDevice::getDeviceInfoWithParameter(cl_device_id id, cl_device_info param, T& value) {

		cl_int status = clGetDeviceInfo(id, param, sizeof(T), &value, nullptr);

		//TODO: check for exception
		ThrowIfCL(status != CL_SUCCESS, status, "clGetDeviceInfo failed");
	}


	// For std::string
	template <> 
	void CLDevice::getDeviceInfoWithParameter<std::string>(cl_device_id id, cl_device_info param, std::string& value);


}





#endif
