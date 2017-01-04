

#ifndef _CE_EXCEPTIONCLIMPL_HPP_
#define _CE_EXCEPTIONCLIMPL_HPP_



#include "Exception.hpp"

#include <string>


namespace CE {


	class ExceptionCLImpl : public Exception {

	public:

		ExceptionCLImpl(std::string what) : 
			msg(what) {
		}

		char const* what() const override { 
			return msg.c_str(); 
		}

		~ExceptionCLImpl() {

		}

	private:
		std::string msg;
	};




}





#endif
