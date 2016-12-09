
#ifndef _CE_FUNCTIONSEQUENTIAL_HPP_
#define _CE_FUNCTIONSEQUENTIAL_HPP_

#include "Function.hpp"

#include <functional>
#include <vector>

namespace CE {

	class FunctionSequential : public Function {

	public:

		FunctionSequential();

		// Inherited via Function
		virtual void setArg(size_t idx, size_t arg_size, void * arg) override;
		virtual void setArg(size_t idx, Buffer const * arg) override;




	private:

		std::function<void(int)> f;
		std::vector<void*> parameters;

	};


}





#endif


