
#ifndef _HQ_THREADSAFEQUEUE_H_
#define _HQ_THREADSAFEQUEUE_H_

#include <condition_variable>
#include <atomic>
#include <mutex>
#include <thread>
#include <queue>
#include <future>

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


		void popWait(T& element) {
			std::unique_lock<std::mutex> lock(queueMutex);
			condition.wait(lock, [this]() { return !localQueue.empty(); });

			element = std::move(localQueue.front());
			localQueue.pop();
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


}


#endif