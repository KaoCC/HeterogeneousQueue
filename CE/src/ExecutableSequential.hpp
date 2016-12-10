#ifndef _CE_EXECUTABLESEQUENTIAL_HPP_
#define _CE_EXECUTABLESEQUENTIAL_HPP_


#include "Executable.hpp"

#include <map>
#include <string>

namespace CE {

	class ExecutableSequential : public Executable {



	public:

		// Inherited via Executable
		virtual Function * createFunction(char const * name) override;
		virtual void deleteFunction(Function * func) override;

	private:

		std::map<std::string, Function*> functionTable;

	};
}



#endif


