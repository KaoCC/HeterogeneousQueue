
#include "ComputeUnit.hpp"
#include "Device.hpp"
#include "Executable.hpp"

#include <functional>

namespace HQ {


	ComputeUnit::ComputeUnit(CE::ComputeEngine* ce, size_t index) : ceRef(ce) {
		// tmp
		device = ce->createDevice(index);

		CE::DeviceSpec spec;
		device->getSpec(spec);
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

	void ComputeUnit::submit(CE::Function const* f, size_t globalSize) {

		//auto runFunction = std::bind(&CE::Device::execute, device , f, 0, globalSize, 0);

		// Mutex here ?
		//tmp
		//device->execute(f, 0, globalSize, 0);

		// KAOCC: need to change the Event parameter !!!
		pool.enqueue(std::bind(&CE::Device::execute, device, f, 0, globalSize, 0, nullptr));
	}

	CE::Executable * ComputeUnit::createSequentialExecutable(const ComputeUnit& cu) {

		CE::Executable* program = nullptr;

		CE::DeviceSpec spec;
		cu.device->getSpec(spec);
		if (spec.type == CE::DeviceType::kSequential) {
			program = CreateSequentialExecutable(cu.device);
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


