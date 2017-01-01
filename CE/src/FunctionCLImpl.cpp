#include "FunctionCLImpl.hpp"
#include "ExceptionCLImpl.hpp"
#include "CLException.hpp"

namespace CE {

	void FunctionCLImpl::setArg(size_t idx, size_t arg_size, void * arg) {

		try {

			kernel.setArg(idx, arg_size, arg);

		} catch (CLAL::CLException& e) {
			throw ExceptionCLImpl(e.what());
		}

	}

	void FunctionCLImpl::setArg(size_t idx, Buffer const * arg) {
		// YET TO BE DONE !!
	}

}
