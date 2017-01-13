
#include "ComputeUnit.hpp"
#include "Device.hpp"
#include "Executable.hpp"

#include <functional>

namespace HQ {


	ComputeUnit::ComputeUnit(CE::ComputeEngine* ce, size_t index) :
		ceRef ( ce ),
		device( ceRef->createDevice(index) ),
		spec(device->getSpec()),
		pool(spec.isThreadSafe ? 0 : 1) {
		// KAOCC: NOTE: 0 for auto-test

		// tmp
		//device = ce->createDevice(index);

		//CE::DeviceSpec spec;
		//device->getSpec(spec);
		//if (spec.type == CE::DeviceType::kSequential) {
		//	
		//	// put it here or user space ?
		//	// KAOCC: put it here perhaps
		//	program = CreateSequentialExecutable(device);
		//	
		//}

		// thread ?

	}

	ComputeUnit::~ComputeUnit() {
		ceRef->deleteDevice(device);
	}

	// should be removed
	CE::Device * ComputeUnit::getDevice() const {
		return device;
	}

	void ComputeUnit::submit(CE::Function const* f, size_t globalSize, CE::Event** evt) {

		//auto runFunction = std::bind(&CE::Device::execute, device , f, 0, globalSize, 0);

		// Mutex here ?
		//tmp
		//device->execute(f, 0, globalSize, 0);

		// KAOCC: need to change the Event parameter !!!
		// Check the local size

		const size_t tmpLocalSize = 64;
		pool.enqueue(std::bind(&CE::Device::execute, device, f, 0, globalSize, tmpLocalSize, evt));
	}

	CE::Executable * ComputeUnit::createSequentialExecutable(const ComputeUnit& cu) {

		CE::Executable* program = nullptr;

		CE::DeviceSpec spec = cu.device->getSpec();
		if (spec.type == CE::DeviceType::kSequential) {
			program = CreateSequentialExecutable(cu.device);
		}

		return program;


	}

	// tmp  impl.
	CE::Executable * ComputeUnit::compileExecutableFromFile(const ComputeUnit & cu, char const * filename, char const * options) {
		

		CE::Executable* program = nullptr;

		CE::DeviceSpec spec = cu.device->getSpec();
		if (spec.type == CE::DeviceType::kGpu || spec.type == CE::DeviceType::kCpu) {
			program = cu.device->compileExecutable(filename, nullptr, 0, options);
		}

		return program;
	}

	//CE::Function* ComputeUnit::createSequentialFunction(const char* name, std::function<void(int)>&& f) {

	//	CE::Function* func = nullptr;

	//	CE::DeviceSpec spec;
	//	device->GetSpec(spec);
	//	if (spec.type == CE::DeviceType::kSequential) {
	//		func = CreateSequentialFunction(program, name, std::move(f));
	//	}

	//	return func;


	//}

}


