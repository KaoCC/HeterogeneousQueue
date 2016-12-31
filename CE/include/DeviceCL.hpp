
#ifndef _CE_DEVICECL_HPP_
#define _CE_DEVICECL_HPP_

#include <CL/cl.h>

#include "Device.hpp"

namespace CE {

	class DeviceCL : public Device {
	public:
		DeviceCL() = default;
		virtual ~DeviceCL() = default;

		virtual Buffer* createBuffer(cl_mem buffer) = 0;
	};

}







#endif