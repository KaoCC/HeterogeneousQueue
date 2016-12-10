#include "DeviceSequential.hpp"
#include "ExecutableSequential.hpp"
#include "FunctionSequential.hpp"

namespace CE {

	void CE::DeviceSequential::GetSpec(DeviceSpec & spec) {
	}


	// this one needs to be changed.
	Platform CE::DeviceSequential::GetPlatform() const {
		return Platform::kMix;
	}

	Buffer * CE::DeviceSequential::createBuffer(size_t size, size_t flags) {
		return nullptr;
	}

	Buffer * CE::DeviceSequential::createBuffer(size_t size, size_t flags, void * data) {
		return nullptr;
	}

	void CE::DeviceSequential::deleteBuffer(Buffer * buffer) {

		if (buffer) {
			delete buffer;
		}
	}

	Executable * CE::DeviceSequential::compileExecutable(char const * source_code, size_t size, char const * options) {
		return nullptr;
	}


	// TODO: for loop ?
	void CE::DeviceSequential::execute(Function const * func, size_t queue, size_t global_size, size_t local_size) {

		//KAOCC: dynamic cast?
		const FunctionSequential* funcSeq = static_cast<const FunctionSequential*>(func);
		auto execFunc = funcSeq->getFunction();

		// execute through the ND-Range sequentially
		for (size_t i = 0; i < global_size; ++i) {
			execFunc(i);
		}

	}

	// Global access functions for APIs

	Executable * DeviceSequential::createExecutable() {
		return new ExecutableSequential();
	}


	Executable * CreateSequentialExecutable(Device * device) {

		//change to dynamic cast perhaps ?
		DeviceSequential* deviceSeq = static_cast<DeviceSequential*>(device);

		return deviceSeq->createExecutable();


	}

}
