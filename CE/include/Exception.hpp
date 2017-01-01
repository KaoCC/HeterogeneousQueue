#ifndef _CE_EXCEPTION_HPP_
#define _CE_EXCEPTION_HPP_



#include "CE_common.hpp"




namespace CE {

	class Exception {

	public:
		// primitive type for interface...
		virtual char const* what() const = 0;
		virtual ~Exception() = 0;
	};

}








#endif