#include "DeviceCLImpl.hpp"
#include "BufferCLImpl.hpp"
#include "CLBuffer.hpp"

namespace CE {

	///// YET TO BE DONE !!!!

	void CE::DeviceCLImpl::GetSpec(DeviceSpec & spec) {
	}

	Platform CE::DeviceCLImpl::GetPlatform() const {
		return Platform();
	}

	Buffer * CE::DeviceCLImpl::createBuffer(size_t size, size_t flags) {
		// KAOCC: FIXME: use flags and change CL_MEM_READ_WRITE
		return new BufferCLImpl(context.createBuffer<char>(size, CL_MEM_READ_WRITE));
	}

	Buffer * CE::DeviceCLImpl::createBuffer(size_t size, size_t flags, void * data) {
		return nullptr;
	}

	void CE::DeviceCLImpl::deleteBuffer(Buffer * buffer) {
	}

	Executable * CE::DeviceCLImpl::compileExecutable(char const * source_code, size_t size, char const * options) {
		return nullptr;
	}

	void CE::DeviceCLImpl::execute(Function const * func, size_t queue, size_t global_size, size_t local_size) {
	}

	Buffer * CE::DeviceCLImpl::createBuffer(cl_mem buf) {

		// KAOCC: TODO: check exception!

			return new BufferCLImpl(CLAL::CLBuffer<char>::createFromBufferCL(buf));

	}


	///// YET TO BE DONE !!!!



}
