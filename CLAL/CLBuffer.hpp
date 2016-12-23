
#ifndef _CLAL_CLBUFFER_HPP_
#define _CLAL_CLBUFFER_HPP_

#include "CLReferenceCount.hpp"


namespace CLAL {

	class CLBuffer : public ReferenceCount<cl_mem, clRetainMemObject, clReleaseMemObject> {



	};


}


#endif
