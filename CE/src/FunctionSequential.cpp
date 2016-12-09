#include "FunctionSequential.hpp"


namespace CE {

	FunctionSequential::FunctionSequential() {

	}

	void FunctionSequential::setArg(size_t idx, size_t arg_size, void * arg) {

		// tmp impl

		if (idx > parameters.size()) {
			parameters.resize(idx);
			// or report error ?
		}

		// check for validation ?
		parameters[idx] = arg;


	}

	void FunctionSequential::setArg(size_t idx, Buffer const * arg) {
		// yet to be done
	}


}




