


#ifndef _CLAL_CLPROGRAM_HPP_
#define _CLAL_CLPROGRAM_HPP_

#include "CLReferenceCount.hpp"
#include "CLKernel.hpp"

#include <map>

namespace CLAL {

	class CLContext;
	//class CLKernel;

	class CLProgram : public ReferenceCount<cl_program, clRetainProgram, clReleaseProgram> {


	public:

		static CLProgram createFromSource(const CLContext& context, char const* sourcecode, size_t sourcesize, char const* buildopts);
		static CLProgram createFromFileName(const CLContext& context, char const* filename, char const* buildopts);
		static CLProgram createFromFileName(const CLContext& context, char const* filename, char const** headernames, size_t numheaders, char const* buildopts);

		size_t getKernelCount() const;
		CLKernel getKernel(std::string const& funcName) const;

		virtual ~CLProgram();

	private:

		// ctor for cl_program wrapper
		CLProgram(cl_program program);



		std::map<std::string, CLKernel> kernelTable;

	};


}





#endif


