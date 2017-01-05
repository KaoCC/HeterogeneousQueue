#include "DeviceCLImpl.hpp"
#include "BufferCLImpl.hpp"
#include "ExceptionCLImpl.hpp"
#include "ExecutableCLImpl.hpp"
#include "FunctionCLImpl.hpp"
#include "CLBuffer.hpp"
#include "Event.hpp"

namespace CE {

	///// Need TO CHECK !!!!

	void CE::DeviceCLImpl::getSpec(DeviceSpec & spec) {
		// MORE HERE !!!!!!
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

	Executable * CE::DeviceCLImpl::compileExecutable(char const * source, size_t size, char const * options) {

		std::string buildopts = options ? options : "";

		// OpenCL 2.0 & include dir
		buildopts.append(" -cl-std=CL2.0 -I . ");


		try {

			return new ExecutableCLImpl(CLAL::CLProgram::createFromSource(context, source, size, buildopts.c_str()));
		} catch (CLAL::CLException& e) {
			throw ExceptionCLImpl(e.what());
		}

	}


	void CE::DeviceCLImpl::execute(Function const * func, size_t queue, size_t globalSize, size_t localSize) {


		const FunctionCLImpl* functionCL = static_cast<const FunctionCLImpl*>(func);

		try {

			CLAL::CLEvent evt = context.execute1D(queue, globalSize, localSize, functionCL->getKernel());

			// ignore the Event ????

		} catch (CLAL::CLException& e) {
			throw ExceptionCLImpl(e.what());
		}


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

			CLAL::CLEvent evt = context.readBuffer(queue, bufferCL->getData(), static_cast<char*>(dst), offset, size);


			if (e) {
				// KAOCC: More here for event handling ...
				// Yet to be done!
			}

		} catch (CLAL::CLException& e) {
			throw ExceptionCLImpl(e.what());
		}



	}

	void DeviceCLImpl::writeBuffer(Buffer const * buffer, size_t queue, size_t offset, size_t size, void * src, Event ** e) {

		const BufferCLImpl* bufferCL = static_cast<const BufferCLImpl*>(buffer);

		try {

			CLAL::CLEvent event = context.writeBuffer(queue, bufferCL->getData(), static_cast<char*>(src), offset, size);


			if (e) {
				// KAOCC: More here for event handling ...
				// Yet to be done!
			}

		} catch (CLAL::CLException& e) {
			throw ExceptionCLImpl(e.what());
		}

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


	///// Need TO CHECK !!!!



}
