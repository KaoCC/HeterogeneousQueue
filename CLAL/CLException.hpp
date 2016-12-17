
#ifndef _CLAL_CLEXCEPTION_HPP_
#define _CLAL_CLEXCEPTION_HPP_

#include <string>
#include <stdexcept>


// OpenCL
#include <CL/cl.h>

namespace CLAL {




	class CLException : public std::runtime_error {
	public:
		CLException(cl_int errcode, const std::string& message);

		// OpenCL Error Code
		cl_int errorCode;
	};




	void ThrowIfCL(bool condition, cl_int errcode, const std::string& message);

}





#endif
