
#include "ComputeEngine.hpp"
#include "ComputeEngineMix.hpp"



namespace CE {

    ComputeEngine::~ComputeEngine() {
    }



	ComputeEngine* CreateComputeEngine(CE::Platform type) {

		ComputeEngine* ret = nullptr;

		if (type == CE::kMix) {
			ret = new CE::ComputeEngineMix();
		}


		// return nullptr if not yet supported
		return ret;
	}

	void DeleteComputeEngine(ComputeEngine* ce) {
		if (ce) {
			delete ce;
		}
	}

}





