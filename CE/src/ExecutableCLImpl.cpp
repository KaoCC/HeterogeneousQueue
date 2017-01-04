#include "ExecutableCLImpl.hpp"
#include "FunctionCLImpl.hpp"
#include "ExceptionCLImpl.hpp"
#include "CLException.hpp"

namespace CE {

	ExecutableCLImpl::ExecutableCLImpl(CLAL::CLProgram prog) : program(prog) {
	}

	Function * ExecutableCLImpl::createFunction(char const * name) {

		try {
			// return a pointer to implement C++ poly.
			return new FunctionCLImpl(program.getKernel(name));

		} catch (CLAL::CLException& e) {
			throw ExceptionCLImpl(e.what());
		}

	}

	void ExecutableCLImpl::deleteFunction(Function * func) {
		// no checking !
		delete func;
	}

	ExecutableCLImpl::~ExecutableCLImpl() {
	}

}
