#ifndef _HQ_COMPUTEUNIT_HPP_
#define _HQ_COMPUTEUNIT_HPP_

#include "ComputeEngine.hpp"
#include "Device.hpp"

#include <functional>

namespace HQ {

	class ComputeUnit {

	public:
		ComputeUnit(CE::ComputeEngine* ce, size_t index);
		~ComputeUnit();

		// KAOCC: this should be removed
		CE::Device* getDevice() const;

		void exeucte(CE::Function const* f, size_t globalSize);

		CE::Function* createSequentialFunction(const char* name, std::function<void(int)>&& f);

	private:

		CE::Device* device {nullptr};
		CE::Executable* program {nullptr};

	};

}


#endif


