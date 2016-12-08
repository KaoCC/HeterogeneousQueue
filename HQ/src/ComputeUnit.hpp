#ifndef _COMPUTE_UNIT_HPP_
#define _COMPUTE_UNIT_HPP_

#include "ComputeEngine.hpp"
#include "Device.hpp"

namespace HQ {

	class ComputeUnit {

	public:
		ComputeUnit(CE::ComputeEngine* ce, size_t index);


	private:

		CE::Device* device;

	};

}


#endif
