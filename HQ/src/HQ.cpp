


#include "HQ.hpp"
#include "ThreadPool.hpp"

namespace HQ {

    static ThreadPool* tp = nullptr;


    void hqInit() {

        if (!tp) {
            tp = new ThreadPool();
        }

    }


    void hqDestroy() {

        if (tp) {
            delete tp;
        }

    }

    void hqEnqueue(Task* task) {
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








