
#include "ComputeEngine.hpp"




namespace CE {

    ComputeEngine::~ComputeEngine() {
    }



	ComputeEngine* CreateComputeEngine() {
		// not yet supported
		return nullptr;
	}

	void DeleteComputeEngine(ComputeEngine* ce) {
		if (ce) {
			delete ce;
		}
	}

}





