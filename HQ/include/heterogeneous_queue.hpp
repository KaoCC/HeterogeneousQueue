
#ifndef _HQ_HETEROGENEOUS_QUEUE_HPP_
#define _HQ_HETEROGENEOUS_QUEUE_HPP_

#include <vector>
#include <thread>
#include <queue>

#include <mutex>
#include <condition_variable>

#include <boost/fiber/all.hpp>

namespace hq {

class nonblocking_callable {
public:
    virtual ~nonblocking_callable() = 0;
};

nonblocking_callable::~nonblocking_callable() {
}

template<class T>
class heterogeneous_queue {

    class thread_worker {
    public:

        thread_worker(heterogeneous_queue& hq_ref) : hq{hq_ref} {
        }

        void operator()() {

            for (auto i = 0; i < fiber_count; ++i) {
                fibers.push_back(boost::fibers::fiber([this]{process_task();}));
            }

            //process_task();
            std::for_each(std::begin(fibers), std::end(fibers), std::mem_fn(&boost::fibers::fiber::join));
        }

    private:

        void process_task() {

            task_t current_task;
            while (hq.task_channel.pop(current_task) != boost::fibers::channel_op_status::closed) {
                current_task();
            }
        }

        std::vector<boost::fibers::fiber> fibers;

        static constexpr unsigned fiber_count = 4;
        heterogeneous_queue& hq;
    };


public:

    using future_t = std::future<T>;

    heterogeneous_queue() {
        auto num_thread = std::thread::hardware_concurrency();

        if (num_thread == 0) {
            num_thread = 2;
        }

        for (auto i = 0; i < num_thread; ++i) {
            workers.push_back(std::thread(thread_worker(*this)));
        }

    }

    ~heterogeneous_queue() {

        task_channel.close();
        std::for_each(std::begin(workers), std::end(workers), std::mem_fn(&std::thread::join));

        // test
        std::cout << "Joined" << std::endl;
    }

    heterogeneous_queue(const heterogeneous_queue&) = delete;
    heterogeneous_queue& operator=(const heterogeneous_queue&) = delete;

    // enqueue function
    template<class NonBlockingFunction, class... Args>
    auto enqueue(NonBlockingFunction&& func, Args&&... args) {

        task_t task {std::bind(std::forward<NonBlockingFunction>(func), std::forward<Args>(args)...)};
        auto task_future = task.get_future();

        task_channel.push(std::move(task));

        return task_future;
    }
 
private:

    static constexpr unsigned channel_size = 2048;

    std::vector<std::thread> workers;

    using task_t = std::packaged_task<T()>;
    boost::fibers::buffered_channel<task_t> task_channel {channel_size};
 

    // ?
    // bool stop;
};




}


#endif
