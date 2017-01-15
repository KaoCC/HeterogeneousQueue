#include "DeviceSequential.hpp"
#include "ExecutableSequential.hpp"
#include "FunctionSequential.hpp"

namespace CE {

	DeviceSpec CE::DeviceSequential::getSpec(void) {

		DeviceSpec spec;

		spec.name = "Sequential Device";
		spec.vendor = "KAOCC";
		spec.type = DeviceType::kSequential;
		spec.isThreadSafe = true;


		return spec;
	}


	// this one needs to be changed.
	PlatformType CE::DeviceSequential::getPlatformType() const {
		return PlatformType::kMix;
	}

	// YET TO BE DONE !!!
	Buffer * CE::DeviceSequential::createBuffer(size_t size, size_t flags) {
		return nullptr;
	}

	Buffer * CE::DeviceSequential::createBuffer(size_t size, size_t flags, void * data) {
		return nullptr;
	}

	void CE::DeviceSequential::deleteBuffer(Buffer * buffer) {

		delete buffer;
	}

	Executable * CE::DeviceSequential::compileExecutable(char const * source_code, size_t size, char const * options) {
		return nullptr;
	}


	// TODO: for loop ?
	CE::Event* CE::DeviceSequential::execute(Function const * func, size_t queue, size_t global_size, size_t local_size, bool eventFlag) {

		//KAOCC: dynamic cast?
		const FunctionSequential* funcSeq = static_cast<const FunctionSequential*>(func);
		auto execFunc = funcSeq->getFunction();

		Event* retEvent = nullptr;

		// execute through the ND-Range sequentially
		for (size_t i = 0; i < global_size; ++i) {
			execFunc(i);
		}

		// KAOCC: FIXME: Event handling
		if (eventFlag) {
			//retEvent = ...
		}

		// tmp
		return retEvent;
	}


	Executable * DeviceSequential::createExecutable() {
		return new ExecutableSequential();
	}

	Executable * DeviceSequential::compileExecutable(char const * fileName, char const ** headerNames, size_t numheaders, char const * options) {
		return nullptr;
	}

	void DeviceSequential::mapBuffer(Buffer const * buffer, size_t queue, size_t offset, size_t size, size_t map_type, void ** mapdata, Event ** e) {
		throw "Yet to be done";
	}

	void DeviceSequential::unmapBuffer(Buffer const * buffer, size_t queue, void * mapdata, Event ** e) {
		throw "Yet to be done";
	}

	void DeviceSequential::deleteEvent(Event * e) {
		throw "Yet to be done";
	}

	void DeviceSequential::readBuffer(Buffer const * buffer, size_t queue, size_t offset, size_t size, void * dst, Event ** e) const {
		throw "Yet to be done";
	}

	void DeviceSequential::writeBuffer(Buffer const * buffer, size_t queue, size_t offset, size_t size, void * src, Event ** e) {
		throw "Yet to be done";
	}

	void DeviceSequential::deleteExecutable(Executable * executable) {
		delete executable;
	}

	void DeviceSequential::waitForEvent(Event * e) {
		throw "Yet to be done";
	}

	void DeviceSequential::flush(size_t queue) {
		throw "Yet to be done";
	}

	void DeviceSequential::finish(size_t queue) {
		throw "Yet to be done";
	}


	// Global access functions for APIs

	CE_API Executable * CreateSequentialExecutable(Device * device) {

		// KAOCC: change to dynamic cast;
		DeviceSequential* deviceSeq = dynamic_cast<DeviceSequential*>(device);
		

		if (deviceSeq != nullptr) {
			return deviceSeq->createExecutable();
		} else {
			return nullptr;
		}


	}

}
