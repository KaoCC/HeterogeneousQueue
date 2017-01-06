#ifndef _HQ_COMPUTEUNIT_HPP_
#define _HQ_COMPUTEUNIT_HPP_

#include "ComputeEngine.hpp"
#include "Device.hpp"
#include "ThreadPool.hpp"

#include <functional>

namespace HQ {

	class ComputeUnit {

	public:
		ComputeUnit(CE::ComputeEngine* ce, size_t index);
		~ComputeUnit();

		// KAOCC: this should be removed
		CE::Device* getDevice() const;

		void submit(CE::Function const* f, size_t globalSize);

		//CE::Function* createSequentialFunction(const char* name, std::function<void(int)>&& f);

		//KAOCC: this one should be move out from the class (static member func or global func)
		// the interface for this class should be kept in a general form
		static CE::Executable* createSequentialExecutable(const ComputeUnit& cu);

	private:

		CE::Device* device {nullptr};
		//CE::Executable* program {nullptr};

		ThreadPool pool;

	};

}


#endif


