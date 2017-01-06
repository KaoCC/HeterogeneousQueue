
#ifndef _CE_CE_HPP_
#define _CE_CE_HPP_


#include "CE_common.hpp"


namespace CE {

	class Device;

    class CE_API ComputeEngine {

    public:


		// KAOCC: FIXME: get platform spec ??

		virtual Device* createDevice(size_t index) = 0;
		virtual void deleteDevice(Device* device) = 0;
		virtual size_t getDeviceCount() const = 0;


		virtual PlatformType getPlatformType() const = 0;

        virtual ~ComputeEngine();



    };




	CE_API ComputeEngine* CreateComputeEngine(CE::PlatformType type);
	CE_API void DeleteComputeEngine(ComputeEngine* ce);




}



#endif







