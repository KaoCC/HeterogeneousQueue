


#include "HQ.hpp"
#include "ThreadPool.hpp"

#include "HeterogeneousQueue.hpp"

namespace HQ {

    static HeterogeneousQueue* hq = nullptr;


    void CreateHeterogeneousQueue() {

        if (!hq) {
			hq = new HeterogeneousQueue();
        }

    }


    void DestroyHeterogeneousQueue() {

        if (hq){
            delete hq;
        }

    }

    void EnqueueHeterogeneousQueue(Task* task) {
        if (hq) {
			hq->enqueue(task);
        }
    }

	//HQAPI CE::Function const* CreateSequentialFunctionWithIndex(size_t index, const char* name, std::function<void(int)>&& f) {

	//	CE::Function const* func = hq->getPlatfrom().getComputeUnit(index)->createSequentialFunction(name, std::move(f));

	//	return func;
	//}

	HQAPI CE::Executable * CreateSequentialExecutableWithIndex(size_t index) {
		// This impl. should be changed
		CE::Executable* exec = ComputeUnit::createSequentialExecutable(*(hq->getPlatfrom().getComputeUnit(index)));
		return exec;
	}

	HQAPI CE::Executable * CompileExecutableWithIndex(size_t index, const char* filename, const char* options) {

		CE::Executable* exec = ComputeUnit::compileExecutableFromFile(*(hq->getPlatfrom().getComputeUnit(index)), filename, options);

		return exec;
	}

	HQAPI size_t HQ::GetNumberOfUnits() {
		return hq->getNumberOfUnitOnPlatform();
	}


    Task::~Task() {
    }

	TaskParameter::~TaskParameter() {
	}

    Event::~Event() {
    }


} 








