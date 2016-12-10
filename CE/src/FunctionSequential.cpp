#include "FunctionSequential.hpp"


namespace CE {

	FunctionSequential::FunctionSequential(const char* str) : name (str) {



	}


	void FunctionSequential::setArg(size_t idx, size_t arg_size, void * arg) {

		// rebind perhaps ?
		// yet to be done
	}

	void FunctionSequential::setArg(size_t idx, Buffer const * arg) {
		// yet to be done
	}


	const std::string FunctionSequential::getName() const {
		return name;
	}

	void FunctionSequential::setFunctionBinding(std::function<void(int)>&& f) {

		this->f = f;
	}


}




