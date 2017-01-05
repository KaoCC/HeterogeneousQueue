#include "FunctionCLImpl.hpp"
#include "ExceptionCLImpl.hpp"
#include "BufferCLImpl.hpp"
#include "CLException.hpp"

namespace CE {
	FunctionCLImpl::FunctionCLImpl(CLAL::CLKernel kern) : kernel(std::move(kern)) { // do you have the move ctor ?
	}


	void FunctionCLImpl::setArg(size_t idx, size_t arg_size, void * arg) {

		try {

			kernel.setArg(idx, arg_size, arg);

		} catch (CLAL::CLException& e) {
			throw ExceptionCLImpl(e.what());
		}

	}

	void FunctionCLImpl::setArg(size_t idx, Buffer const * arg) {

		try {

			const BufferCLImpl* buffCL = static_cast<const BufferCLImpl*>(arg);
			kernel.setArg(idx, buffCL->getData());

		} catch (CLAL::CLException& e) {
			throw ExceptionCLImpl(e.what());

		}

	}

	CLAL::CLKernel FunctionCLImpl::getKernel() const {
		return kernel;
	}

}
