


#ifndef _CLAL_CLPROGRAM_HPP_
#define _CLAL_CLPROGRAM_HPP_

#include "CLReferenceCount.hpp"
#include "CLKernel.hpp"

#include <map>

namespace CLAL {

	class CLProgram : public ReferenceCount<cl_program, clRetainProgram, clReleaseProgram> {


	public:


		size_t getKernelCount() const;
		CLKernel GetKernel(std::string const& funcName) const;

		virtual ~CLProgram();

	private:

		// ctor for cl_program wrapper
		CLProgram(cl_program program);



		std::map<std::string, CLKernel> kernels;

	};


}





#endif


