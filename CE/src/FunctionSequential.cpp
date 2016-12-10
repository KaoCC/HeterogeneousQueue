#include "FunctionSequential.hpp"


namespace CE {

	FunctionSequential::FunctionSequential(const char* str) : name (str) {

	}

	FunctionSequential::FunctionSequential(const char * name) {
	}

	void FunctionSequential::setArg(size_t idx, size_t arg_size, void * arg) {

		// yet to be done
	}

	void FunctionSequential::setArg(size_t idx, Buffer const * arg) {
		// yet to be done
	}


	const std::string FunctionSequential::getName() const {
		return name;
	}


}




