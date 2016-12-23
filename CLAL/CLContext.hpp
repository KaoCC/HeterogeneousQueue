
#ifndef _CLAL_CLCONTEXT_HPP_
#define _CLAL_CLCONTEXT_HPP_


#include "CLReferenceCount.hpp"


namespace CLAL {


	class CLContext : public ReferenceCount<cl_context, clRetainContext, clReleaseContext> {





	};


}




#endif


