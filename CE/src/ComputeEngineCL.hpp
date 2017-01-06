

#ifndef _CE_COMPUTEENGINECL_HPP_
#define _CE_COMPUTEENGINECL_HPP_


#include "ComputeEngine.hpp"
#include "CLPlatform.hpp"
#include "CLDevice.hpp"

#include <vector>

namespace CE {

	class ComputeEngineCL : public ComputeEngine {

	public:


		ComputeEngineCL();
		~ComputeEngineCL() = default;


		// Inherited via ComputeEngine
		virtual Device * createDevice(size_t index) override;

		virtual void deleteDevice(Device * device) override;

		virtual size_t getDeviceCount() const override;

		virtual PlatformType getPlatformType() const override;






	private:

		std::vector<CLAL::CLPlatform> platforms;
		std::vector<CLAL::CLDevice> devices;

	};


}








#endif
