
#include "ThreadPool.hpp"
#include "Worker.hpp"

#include <iostream>

namespace HQ {

	Worker::Worker(ThreadPool& pool) : poolRef (pool), id(0) {
		id = worker_count;
		std::cerr << "Worker created " << id << " " <<std::this_thread::get_id() << std::endl;
		++worker_count;
	}


	void Worker::operator() () {

		Task* task = nullptr;

		while (!poolRef.done) {

			if (poolRef.taskQueue.pop(task)) {

				auto& runFunction = task->getRunFunction();
				runFunction(task->getTaskParameter());

				//TODO: check for event ?

				Event* event = task->getEvent();
				if (event) {
					event->signal();
				}


			} else {
				std::this_thread::sleep_for(std::chrono::milliseconds(poolRef.sleepTime));
			}

		}
	}



	Worker::~Worker() {
		std::cerr << "Worker del " <<  id << " " << std::this_thread::get_id() <<std::endl;
	}



}


