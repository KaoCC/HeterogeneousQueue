#ifndef _CE_COMPUTEENGINEMIX_HPP_
#define _CE_COMPUTEENGINEMIX_HPP_

#include "ComputeEngine.hpp"

namespace CE {

	class ComputeEngineMix : public ComputeEngine {

	public:
		ComputeEngineMix();

		size_t getDeviceCount() const override;

		Platform getPlatform() const override;

		// Inherited via ComputeEngine
		virtual Device * createDevice(size_t index) const override;
		virtual void deleteDevice(Device * device) override;


	private:
		// test
		static const size_t NUM_OF_DEVICE = 1;

		// default: sequential CPU + all GPU in CL
		Device* device[NUM_OF_DEVICE];

	};

}




#endif