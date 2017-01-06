
#ifndef _CE_CE_HPP_
#define _CE_CE_HPP_


#include "CE_common.hpp"


namespace CE {

	class Device;

    class CE_API ComputeEngine {

    public:


		virtual Device* createDevice(size_t index) = 0;
		virtual void deleteDevice(Device* device) = 0;
		virtual size_t getDeviceCount() const = 0;


		virtual PlatformType getPlatformType() const = 0;

        virtual ~ComputeEngine() = 0;


    };




	CE_API ComputeEngine* CreateComputeEngine(CE::PlatformType type);
	CE_API void DeleteComputeEngine(ComputeEngine* ce);




}



#endif







