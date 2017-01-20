
#include "ComputeUnit.hpp"
#include "Device.hpp"
#include "Executable.hpp"

#include "HQ.hpp"
#include "Event.hpp"

#include <functional>

namespace HQ {


	ComputeUnit::ComputeUnit(CE::ComputeEngine* ce, size_t index) :
		indexID(index),
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

	std::future<CE::Event*> ComputeUnit::submit(Task * task) {

		auto eventFuture = pool.enqueue(std::bind(execution, std::ref(*this), task));

		return eventFuture;
	}

	//std::future<CE::Event*> ComputeUnit::submit(CE::Function const* f, size_t globalSize, bool eventFlag) {

	//	//auto runFunction = std::bind(&CE::Device::execute, device , f, 0, globalSize, 0);

	//	// Mutex here ?
	//	//tmp
	//	//device->execute(f, 0, globalSize, 0);

	//	// KAOCC: need to change the Event parameter !!!
	//	// Check the local size

	//	auto eventFuture = pool.enqueue(std::bind(execution, device, f, globalSize, eventFlag));
	//	return eventFuture;
	//}

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


	CE::Event * ComputeUnit::execution(const ComputeUnit& cu, Task * task) {

		//NOTE: MAKE SURE EVERYTHING HERE CAN BE EXECUTED IN PARALLEL !!!!!!!
		// ex: Createbuffer, Read, Write, Exec with CL Queue

		// get the device from CU
		CE::Device* dev = cu.getDevice();

		// get the function from task
		CE::Function* func = task->getRunFunction(cu.indexID);

		// get number of parameters
		size_t numOfParams = task->getNumOfParameters();

		// records for buffers
		std::vector<CE::Buffer*> buffers(numOfParams);


		for (size_t i = 0; i < numOfParams; ++i) {

			// get Task parameters from the task
			TaskParameter* taskParam = task->getTaskParameter(i);

			// create buffers based on the parameters
			// KAOCC: flag is not used (0)
			buffers[i] = dev->createBuffer(taskParam->getSizeInByte(), 0, taskParam->getData());

			// copy buffers (kernel set Args ?)

			// Seems like we dont need to write ?
			//dev->writeBuffer();

			// kernel set Args 
			func->setArg(i, buffers[i]);
		}

		const size_t tmpLocalSize = 64;
		CE::Event* evt = dev->execute(func, 0, task->getGlobalSize(), tmpLocalSize, true);
		evt->wait();

		// when done ..

		// copy the buffer back to host
		for (size_t i = 0; i < numOfParams; ++i) {

			TaskParameter* taskParam = task->getTaskParameter(i);

			// KAOCC: Queue index is always 0 in the current impl.
			// KAOCC: Event is set to nullptr
			dev->readBuffer(buffers[i], 0, 0, taskParam->getSizeInByte(), taskParam->getData(), nullptr);

		}


		// relese event

		dev->deleteEvent(evt);

		// destroy buffers

		// ???

		for (size_t i = 0; i < numOfParams; ++i) {
			dev->deleteBuffer(buffers[i]);
		}



		// test !!!
		// Need to change the Event system
		Event* event = task->getEvent();
		if (event) {
			event->signal();
		}

		// what to return ?

		return nullptr;
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


