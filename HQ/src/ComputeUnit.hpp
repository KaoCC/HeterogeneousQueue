#ifndef _HQ_COMPUTEUNIT_HPP_
#define _HQ_COMPUTEUNIT_HPP_

#include "ComputeEngine.hpp"
#include "Device.hpp"
#include "ThreadPool.hpp"

#include <functional>


namespace HQ {

	class Task;

	class ComputeUnit {

	public:
		ComputeUnit(CE::ComputeEngine* ce, size_t index);
		~ComputeUnit();


		ComputeUnit(const ComputeUnit& rhs) = delete;
		

		// KAOCC: this should be removed
		CE::Device* getDevice() const;

		//std::future<CE::Event*> submit(CE::Function const* f, size_t globalSize, bool eventFlag);
		//std::future<CE::Event*> submit(Task* f);

		//CE::Function* createSequentialFunction(const char* name, std::function<void(int)>&& f);

		//KAOCC: this one should be move out from the class (static member func or global func)
		// the interface for this class should be kept in a general form
		static CE::Executable* createSequentialExecutable(const ComputeUnit& cu);

		static CE::Executable* compileExecutableFromFile(const ComputeUnit& cu, char const* filename, char const* options);



		void execute(Task* task);


	private:

		// helper
		//static CE::Event* execution(CE::Device* device, CE::Function const* f, size_t globalSize, bool eventFlag) {
		//	const size_t tmpLocalSize = 64;
		//	return device->execute(f, 0, globalSize, tmpLocalSize, true);
		//}

		// to be removed
		//static CE::Event* execution(const ComputeUnit& cu, Task* task);


		// Index
		size_t indexID;

		// ref to ComputeEngine
		CE::ComputeEngine * const ceRefPtr;

		CE::Device* mDevice{nullptr};
		//CE::Executable* program {nullptr};

		// KAOCC: test
		CE::DeviceSpec spec;

		// KAOCC: is the device thread safe ? We need to check in advance
		//ThreadPool<CE::Event*> pool;



	};

}


#endif


