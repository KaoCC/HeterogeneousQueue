


#include "HQ.hpp"
#include "ThreadPool.hpp"

namespace HQ {

    static ThreadPool* tp = nullptr;


    void CreateHeterogeneousQueue() {

        if (!tp) {
            tp = new ThreadPool();
        }

    }


    void DestroyHeterogeneousQueue() {

        if (tp) {
            delete tp;
        }

    }

    void EnqueueHeterogeneousQueue(Task* task) {
        if (tp) {
            tp->enqueue(task);
        }
    }


    Task::~Task() {
    }

	TaskParameter::~TaskParameter() {
	}

    Event::~Event() {
    }


} 








