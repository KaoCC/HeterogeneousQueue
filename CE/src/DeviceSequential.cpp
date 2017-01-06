#include "DeviceSequential.hpp"
#include "ExecutableSequential.hpp"
#include "FunctionSequential.hpp"

namespace CE {

	void CE::DeviceSequential::getSpec(DeviceSpec & spec) {

		spec.name = "Sequential Device";
		spec.vendor = "KAOCC";
		spec.type = DeviceType::kSequential;

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
	void CE::DeviceSequential::execute(Function const * func, size_t queue, size_t global_size, size_t local_size, Event** e) {

		//KAOCC: dynamic cast?
		const FunctionSequential* funcSeq = static_cast<const FunctionSequential*>(func);
		auto execFunc = funcSeq->getFunction();

		// execute through the ND-Range sequentially
		for (size_t i = 0; i < global_size; ++i) {
			execFunc(i);
		}

		// KAOCC: FIXME: Event handling

	}


	Executable * DeviceSequential::createExecutable() {
		return new ExecutableSequential();
	}

	void DeviceSequential::readBuffer(Buffer const * buffer, size_t queue, size_t offset, size_t size, void * dst, Event ** e) const {
	}

	void DeviceSequential::writeBuffer(Buffer const * buffer, size_t queue, size_t offset, size_t size, void * src, Event ** e) {
	}

	void DeviceSequential::deleteExecutable(Executable * executable) {
	}

	void DeviceSequential::waitForEvent(Event * e) {
	}

	void DeviceSequential::flush(size_t queue) {
	}

	void DeviceSequential::finish(size_t queue) {
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
