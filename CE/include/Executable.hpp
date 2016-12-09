#ifndef _CE_EXECUTABLE_HPP_
#define _CE_EXECUTABLE_HPP_

#include "CE_common.hpp"

namespace CE {

	class Function;

	class CE_API Executable {

	public:
		virtual Function* createFunction(char const* name) = 0;
		virtual void deleteFunction(Function* func) = 0;

	};




}





#endif


