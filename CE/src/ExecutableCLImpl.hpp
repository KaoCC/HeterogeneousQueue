#ifndef _CE_EXECUTABLECLIMPL_HPP_
#define _CE_EXECUTABLECLIMPL_HPP_

#include "Executable.hpp"
#include "CLProgram.hpp"

namespace CE {

	class ExecutableCLImpl : public Executable {


	public:
		ExecutableCLImpl(CLAL::CLProgram prog);

		// For Function management
		Function* createFunction(char const* name) override;
		void deleteFunction(Function* func) override;

		~ExecutableCLImpl();



	private:

		CLAL::CLProgram program;

	};

}









#endif
