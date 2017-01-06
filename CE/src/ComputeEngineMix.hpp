#ifndef _CE_COMPUTEENGINEMIX_HPP_
#define _CE_COMPUTEENGINEMIX_HPP_

#include "ComputeEngine.hpp"

namespace CE {

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
		static const size_t NUM_OF_DEVICE = 1;

		// default: sequential CPU + all GPU in CL
		// KAOCC: we should NOT store the actual device instances !!!!!!!
		// TODO: change to device info.
		Device* deviceList[NUM_OF_DEVICE];

	};

}




#endif