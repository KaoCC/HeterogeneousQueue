#include "DeviceCLImpl.hpp"
#include "BufferCLImpl.hpp"
#include "ExceptionCLImpl.hpp"
#include "ExecutableCLImpl.hpp"
#include "FunctionCLImpl.hpp"
#include "CLBuffer.hpp"
#include "EventCLImpl.hpp"

namespace CE {

	///// Need TO CHECK !!!!

	DeviceCLImpl::DeviceCLImpl(CLAL::CLDevice dev) : device(std::move(dev)), context(CLAL::CLContext::create(dev)) {
		initEventPool();
	}

	DeviceCLImpl::DeviceCLImpl(CLAL::CLDevice dev, CLAL::CLContext ctx) :
		device(std::move(dev)), context(std::move(ctx)) {

		initEventPool();
	}

	void CE::DeviceCLImpl::getSpec(DeviceSpec & spec) {
		// MORE HERE !!!!!!
	}

	PlatformType CE::DeviceCLImpl::getPlatformType() const {
		return PlatformType::kOpenCL;;
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
		delete buffer;
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


	void CE::DeviceCLImpl::execute(Function const * func, size_t queue, size_t globalSize, size_t localSize, Event** e) {


		const FunctionCLImpl* functionCL = static_cast<const FunctionCLImpl*>(func);

		try {

			CLAL::CLEvent evt = context.execute1D(queue, globalSize, localSize, functionCL->getKernel());

			// ignore the Event ????
			// KAOCC: FIXME: Event handling 

			if (e) {

			}

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


	// KAOCC: we need to redesign this API ...
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

	DeviceCLImpl::~DeviceCLImpl() {
		while (!eventPool.empty()) {
			auto event = eventPool.front();
			eventPool.pop();
			delete event;
		}
	}

	void DeviceCLImpl::initEventPool() {
		for (size_t i = 0; i < INIT_EVENT_POOL_SIZE; ++i) {
			eventPool.push(new EventCLImpl());
		}
	}


	///// Need TO CHECK !!!!



}
