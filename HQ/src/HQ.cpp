


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

	HQAPI CE::Buffer * CreateBufferWithIndex(size_t index, size_t size) {
		CE::Device* dev = hq->getPlatfrom().getComputeUnit(index)->getDevice();
		CE::Buffer* buffer = dev->createBuffer(size, 0); // note: flag is currently not in used


		return buffer;
	}

	HQAPI CE::Buffer * CreateBufferWithIndex(size_t index, size_t size, void * initData) {
		CE::Device* dev = hq->getPlatfrom().getComputeUnit(index)->getDevice();
		CE::Buffer* buffer = dev->createBuffer(size, 0, initData); // note: flag is currently not in used

		return buffer;
	}

	HQAPI void WriteBufferWithIndex(size_t index, CE::Buffer const * buffer, size_t offset, size_t size, void * src) {

		CE::Device* dev = hq->getPlatfrom().getComputeUnit(index)->getDevice();

		// KAOCC: need to check if the Event can be nullptr
		// Need to check the index of CQ
		dev->writeBuffer(buffer, 0, offset, size, src, nullptr);
	}

	HQAPI void ReadBufferWithIndex(size_t index, CE::Buffer const * buffer, size_t offset, size_t size, void * dst) {

		CE::Device* dev = hq->getPlatfrom().getComputeUnit(index)->getDevice();

		// KAOCC: need to check if the Event can be nullptr
		// Need to check the index of CQ
		dev->readBuffer(buffer, 0, offset, size, dst, nullptr);
	}

	HQAPI void MapBufferWithIndex(size_t index, CE::Buffer const * buffer, size_t offset, size_t size, void ** mapdata) {
		CE::Device* dev = hq->getPlatfrom().getComputeUnit(index)->getDevice();

		// KAOCC: mapType is set to Zero !
		// KAOCC: Event is set to nullptr !
		dev->mapBuffer(buffer, 0, offset, size, 0, mapdata, nullptr);

	}

	HQAPI void UnmapBufferWithIndex(size_t index, CE::Buffer const * buffer, void * mapdata) {
		CE::Device* dev = hq->getPlatfrom().getComputeUnit(index)->getDevice();

		// KAOCC: mapType is set to Zero !
		// KAOCC: Event is set to nullptr !
		dev->unmapBuffer(buffer, 0, mapdata, nullptr);
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








