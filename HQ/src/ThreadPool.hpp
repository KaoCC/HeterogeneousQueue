

#ifndef _THREADPOOL_H_
#define _THREADPOOL_H_

#include <condition_variable>
#include <atomic>
#include <mutex>
#include <thread>
#include <queue>
#include <future>
#include <algorithm>


#include "HQ.hpp"
#include "ThreadSafeQueue.hpp"

namespace HQ {


    class ThreadPool {

    public:

        ThreadPool() {

            unsigned numberOfThreads = std::thread::hardware_concurrency();
            if (!numberOfThreads) {
                numberOfThreads = 4;
            }

            for (size_t i = 0 ; i < numberOfThreads; ++i) {
                workerThreads.push_back(std::thread(&ThreadPool::runLoop, this));
            }

        }

        void enqueue(Task* task) {

            //TODO: may need to add something related to Event...
            taskQueue.push(task);

        }

        size_t getSize() const {
            return taskQueue.size();
        }


        ~ThreadPool() {
            done = true;
            std::for_each(workerThreads.begin(), workerThreads.end(), std::mem_fun_ref(&std::thread::join));
        }


    private:

        void runLoop() {

            Task* task = nullptr;

            while (!done) {

                if (taskQueue.pop(task)) {
                    
                    auto& runFunction = task->getRunFunction();
                    runFunction(task->getTaskParameter());

                    //TODO: check for event ?

                } else {
                    std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
                }

            }

        }



        int sleepTime = 20;
        std::atomic_bool done {false};
        std::vector<std::thread> workerThreads;
        ThreadSafeQueue<Task*> taskQueue;

    };




}




#endif







