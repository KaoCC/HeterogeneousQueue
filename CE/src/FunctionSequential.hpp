
#ifndef _CE_FUNCTIONSEQUENTIAL_HPP_
#define _CE_FUNCTIONSEQUENTIAL_HPP_

#include "Function.hpp"

#include <functional>

namespace CE {

	class FunctionSequential : public Function {

	public:

		// Inherited via Function
		virtual void setArg(size_t idx, size_t arg_size, void * arg) override;

		virtual void setArg(size_t idx, Buffer const * arg) override;

	private:


		std::function<void()> f;

	};


}





#endif