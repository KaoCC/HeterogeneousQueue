#ifndef _CE_COMPUTEENGINEMIX_HPP_
#define _CE_COMPUTEENGINEMIX_HPP_

#include "ComputeEngine.hpp"
#include "CLPlatform.hpp"
#include "CLDevice.hpp"

#include <vector>

namespace CE {


	// KAOCC: This class combines Sequential Device (CPU) in ThreadPool & Vector Devices (GPUs) in CL

	class ComputeEngineMix : public ComputeEngine {

	public:
		ComputeEngineMix();

		size_t getDeviceCount() const override;

		PlatformType getPlatformType() const override;

		// Inherited via ComputeEngine
		virtual Device * createDevice(size_t index) override;
		virtual void deleteDevice(Device * device) override;


	private:
		// test
		//static const size_t NUM_OF_DEVICE = 1;
		
		size_t numberOfDeviceInEngine = 0;

		// default: sequential CPU + all GPU in CL
		// KAOCC: we should NOT store the actual device instances !!!!!!!
		// TODO: change to device info.

		// KAOCC: subject to change or delete
		//Device* deviceList[NUM_OF_DEVICE];



		// CL device and platform list
		std::vector<CLAL::CLPlatform> platforms;
		std::vector<CLAL::CLDevice> devices;

		// CPU Sequential Does not need the list


	};

}




#endif