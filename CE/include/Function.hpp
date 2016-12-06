
#ifndef _CE_FUNCTION_HPP_
#define _CE_FUNCTION_HPP_


#include "CE_common.hpp"

namespace CE {


	class Buffer;

	class CE_API Function {
	public:

		virtual void setArg(size_t idx, size_t arg_size, void* arg) = 0;
		virtual void setArg(size_t idx, Buffer const* arg) = 0;
		//virtual void setArg(size_t idx, size_t size, SharedMemory shmem) = 0;

	};

}




#endif
