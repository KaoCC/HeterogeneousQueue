
#ifndef _CE_FUNCTIONSEQUENTIAL_HPP_
#define _CE_FUNCTIONSEQUENTIAL_HPP_

#include "Function.hpp"

#include <functional>
#include <string>

namespace CE {

	class FunctionSequential : public Function {

	public:

		FunctionSequential(const char* name);


		// Inherited via Function
		virtual void setArg(size_t idx, size_t arg_size, void * arg) override;
		virtual void setArg(size_t idx, Buffer const * arg) override;



		const std::string getName() const;
		void setFunctionBinding(std::function<void(int)>&& f);
		const std::function<void(int)>& getFunction() const;

	private:


		std::function<void(int)> f;
		std::string name;

	};


}





#endif


