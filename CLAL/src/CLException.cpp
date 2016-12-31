#include "CLException.hpp"

namespace CLAL {

	CLException::CLException(cl_int errcode, const std::string & message) : 
		std::runtime_error(message), errorCode(errcode) {
	}



	void ThrowIfCL(bool condition, cl_int errcode, const std::string& message) {
		if (condition)
			throw CLException(errcode, message);
	}

}
