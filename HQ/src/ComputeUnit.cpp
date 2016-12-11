
#include "ComputeUnit.hpp"
#include "Device.hpp"
#include "Executable.hpp"

#include <functional>

namespace HQ {


	ComputeUnit::ComputeUnit(CE::ComputeEngine* ce, size_t index) {
		// tmp
		device = ce->createDevice(index);

		CE::DeviceSpec spec;
		device->GetSpec(spec);
		if (spec.type == CE::DeviceType::kSequential) {
			
			// put it here or user space ?
			// KAOCC: put it here perhaps
			program = CreateSequentialExecutable(device);
			
		}

		// thread ?

	}

	ComputeUnit::~ComputeUnit() {
		// delete ?
	}

	// should be removed
	CE::Device * ComputeUnit::getDevice() const {
		return device;
	}

	void ComputeUnit::exeucte(CE::Function const* f, size_t globalSize) {

		//tmp
		device->execute(f, 0, globalSize, 0);
	}

	CE::Function* ComputeUnit::createSequentialFunction(const char* name, std::function<void(int)>&& f) {

		CE::Function* func = nullptr;

		CE::DeviceSpec spec;
		device->GetSpec(spec);
		if (spec.type == CE::DeviceType::kSequential) {
			func = CreateSequentialFunction(program, name, std::move(f));
		}

		return func;


	}

}


