

#ifndef _THREADPOOL_H_
#define _THREADPOOL_H_

#include <condition_variable>
#include <atomic>
#include <mutex>
#include <thread>
#include <queue>
#include <future>
#include <algorithm>


namespace HQ {


    template <typename T> 
    class ThreadSafeQueue {

    public:

        // rval ref
        void push(T&& rvalRef) {
            std::lock_guard<std::mutex> lock(queueMutex);
            localQueue.push(std::move(rvalRef));
            condition.notify_one();
        }


        // const T ref
        void push(const T& element) {
            std::lock_guard<std::mutex> lock(queueMutex);
            localQueue.push(element);
            condition.notify_one();
        }


        bool pop(T& element) {
            std::lock_guard<std::mutex> lock(queueMutex);
            if (localQueue.empty()) {

                return false;
            } else {

                element = std::move(localQueue.front());
                localQueue.pop();
                return true;    
            }
        }

        size_t size() const {
            std::lock_guard<std::mutex> lock(queueMutex);
            return localQueue.size();
        }



    private:

        mutable std::mutex queueMutex; 
        std::condition_variable condition;
        std::queue<T> localQueue;

    };


    template <typename ReturnType> 
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

        std::future<ReturnType> enqueue(std::function<ReturnType()>&& taskFunc) {

            std::packaged_task<ReturnType()> task(std::move(taskFunc));
            auto futureResult = task.get_future();

            // rval reference
            taskQueue.push(std::move(task));
            return futureResult;

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

            std::packaged_task<ReturnType()> runFunction;

            while (!done) {

                if (taskQueue.pop(runFunction)) {

                    runFunction();

                } else {
                    std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
                }

            }

        }



        int sleepTime = 20;
        std::atomic_bool done {false};
        std::vector<std::thread> workerThreads;
        ThreadSafeQueue<std::packaged_task<ReturnType()> > taskQueue;

    };




}




#endif







