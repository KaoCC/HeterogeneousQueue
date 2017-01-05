#include "DeviceCLImpl.hpp"
#include "BufferCLImpl.hpp"
#include "ExceptionCLImpl.hpp"
#include "ExecutableCLImpl.hpp"
#include "CLBuffer.hpp"
#include "Event.hpp"

namespace CE {

	///// YET TO BE DONE !!!!

	void CE::DeviceCLImpl::getSpec(DeviceSpec & spec) {
		//
	}

	Platform CE::DeviceCLImpl::getPlatform() const {
		return Platform::kOpenCL;;
	}

	Buffer * CE::DeviceCLImpl::createBuffer(size_t size, size_t flags) {


		try {

			// KAOCC: FIXME: use flags and change CL_MEM_READ_WRITE
			return new BufferCLImpl(context.createBuffer<char>(size, CL_MEM_READ_WRITE));
		} catch (CLAL::CLException& e) {
			throw ExceptionCLImpl(e.what());

		}
	}

	Buffer * CE::DeviceCLImpl::createBuffer(size_t size, size_t flags, void * data) {
		// KAOCC: Yet to be done
		return nullptr;
	}

	void CE::DeviceCLImpl::deleteBuffer(Buffer * buffer) {
		if (buffer) {
			delete buffer;
		}
	}

	Executable * CE::DeviceCLImpl::compileExecutable(char const * source_code, size_t size, char const * options) {
		// KAOCC: yet to be done
		return nullptr;
	}

	void CE::DeviceCLImpl::execute(Function const * func, size_t queue, size_t global_size, size_t local_size) {



	}

	Buffer * CE::DeviceCLImpl::createBuffer(cl_mem buf) {

		try {

			return new BufferCLImpl(CLAL::CLBuffer<char>::createFromBufferCL(buf));
		} catch (CLAL::CLException& e) {
			throw ExceptionCLImpl(e.what());
		}

	}

	void DeviceCLImpl::readBuffer(Buffer const * buffer, size_t queue, size_t offset, size_t size, void * dst, Event ** e) const {

		const BufferCLImpl* bufferCL = static_cast<const BufferCLImpl*>(buffer);

		try {

			CLAL::CLEvent event = context.readBuffer(queue, bufferCL->getData(), static_cast<char*>(dst), offset, size);


		} catch (CLAL::CLException& e) {

		}



	}

	void DeviceCLImpl::writeBuffer(Buffer const * buffer, size_t queue, size_t offset, size_t size, void * src, Event ** e) {



	}

	void DeviceCLImpl::deleteExecutable(Executable * executable) {
		delete executable;
	}

	void DeviceCLImpl::waitForEvent(Event * e) {
		e->wait();
	}




	void DeviceCLImpl::flush(size_t queue) {
		try {
			context.flush(queue);
		} catch (CLAL::CLException& e) {
			throw ExceptionCLImpl(e.what());
		}
	}

	void DeviceCLImpl::finish(size_t queue) {
		try {
			context.finish(queue);
		} catch (CLAL::CLException& e) {
			throw ExceptionCLImpl(e.what());
		}
	}


	///// YET TO BE DONE !!!!



}
