
#include "ComputeEngine.hpp"
#include "ComputeEngineMix.hpp"
#include "ComputeEngineCL.hpp"


namespace CE {

    ComputeEngine::~ComputeEngine() {
    }



	ComputeEngine* CreateComputeEngine(CE::PlatformType type) {

		ComputeEngine* ret = nullptr;


		switch (type) {
		case CE::kMix:
			ret = new CE::ComputeEngineMix();
			break;
		case CE::kOpenCL:
			ret = new CE::ComputeEngineCL();
			break;

		default:
			ret = nullptr;
			break;
		}


		// return nullptr if not yet supported
		return ret;
	}

	void DeleteComputeEngine(ComputeEngine* ce) {
		delete ce;
	}

}





