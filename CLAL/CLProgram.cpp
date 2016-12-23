#include "CLProgram.hpp"
#include "CLException.hpp"

namespace CLAL {

	size_t CLProgram::getKernelCount() const {
		return kernels.size();
	}

	CLKernel CLProgram::GetKernel(std::string const & funcName) const {

		auto iter = kernels.find(funcName);

		ThrowIfCL(iter == kernels.end(), CL_INVALID_KERNEL_NAME, "No such kernel in program");

		// copy
		return iter->second;

	}

	CLProgram::~CLProgram() {
	}

}
