
#ifndef _CE_CE_HPP_
#define _CE_CE_HPP_


#include "CE_common.hpp"


namespace CE {

    class CE_API ComputeEngine {

    public:

		virtual size_t GetDeviceCount() const = 0;
        virtual ~ComputeEngine() = 0;


    };




	CE_API ComputeEngine* CreateComputeEngine();
	CE_API void DeleteComputeEngine(ComputeEngine* ce);

}



#endif







