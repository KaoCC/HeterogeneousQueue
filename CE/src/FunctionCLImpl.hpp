

#ifndef _FUNCTIONCLIMPL_HPP_
#define _FUNCTIONCLIMPL_HPP_

#include "Function.hpp"
#include "CLKernel.hpp"

namespace CE {

	class FunctionCLImpl : public Function {


	public:

		// Inherited via Function
		virtual void setArg(size_t idx, size_t arg_size, void * arg) override;

		virtual void setArg(size_t idx, Buffer const * arg) override;


	private:
		CLAL::CLKernel kernel;



	};

}



#endif
