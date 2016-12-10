#include "ExecutableSequential.hpp"
#include "FunctionSequential.hpp"

namespace CE {

	Function * ExecutableSequential::createFunction(char const * name) {

		Function* f = new FunctionSequential(name);
		functionTable[name] = f;
		return f;

	}

	void ExecutableSequential::deleteFunction(Function * func) {

		FunctionSequential* fs = static_cast<FunctionSequential*>(func);


		auto it = functionTable.find(fs->getName());

		if (it != functionTable.end()) {

			delete it->second;
			functionTable.erase(it);
		}


	}

}



