#ifndef _CE_EXECUTABLE_HPP_
#define _CE_EXECUTABLE_HPP_

#include "CE_common.hpp"

#include <functional>

namespace CE {

	class Function;

	class CE_API Executable {

	public:
		virtual Function* createFunction(char const* name) = 0;
		virtual void deleteFunction(Function* func) = 0;

	};


	CE_API Function* CreateSequentialFunction(Executable* exec, const char* name, std::function<void(int)>&& f);

}





#endif


