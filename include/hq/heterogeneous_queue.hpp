
#ifndef _HQ_HETEROGENEOUS_QUEUE_HPP_
#define _HQ_HETEROGENEOUS_QUEUE_HPP_

#include <vector>
#include <thread>
#include <queue>

#include <mutex>
#include <condition_variable>

#include <boost/fiber/all.hpp>

namespace hq {


class heterogeneous_queue {


	class task_base {
	public:
		virtual void execute() = 0;
		virtual ~task_base() = default;
	};

	template<class R>
	class fiber_task : public task_base {

	public:

		using task_t = boost::fibers::packaged_task<R()>;

		fiber_task(task_t&& func) : callable(std::move(func)) {
		}

		void execute() override {
			callable();
		}

		task_t callable;
		
	};


    class thread_worker {
    public:

        thread_worker(heterogeneous_queue& hq_ref) : hq{hq_ref} {
        }

        void operator()() {

            for (auto i = 0; i < fiber_count; ++i) {
                fibers.emplace_back([this] { process_task(); });
            }

            //process_task();
            std::for_each(std::begin(fibers), std::end(fibers), std::mem_fn(&boost::fibers::fiber::join));
        }

    private:

        void process_task() {

			std::unique_ptr<task_base> current_task;
            while (hq.task_channel.pop(current_task) != boost::fibers::channel_op_status::closed) {
                current_task->execute();
            }
        }

        std::vector<boost::fibers::fiber> fibers;

        static constexpr unsigned fiber_count = 4;
        heterogeneous_queue& hq;
    };


public:


    heterogeneous_queue() {
        auto num_thread = std::thread::hardware_concurrency();

        if (num_thread == 0) {
            num_thread = 2;
        }

        for (unsigned i = 0; i < num_thread; ++i) {
            workers.emplace_back(thread_worker(*this));
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
    template<class R, class FiberFunc, class... Args>
    auto enqueue(FiberFunc&& func, Args&&... args) {


        // task_t task {std::bind(std::forward<NonBlockingFunction>(func), std::forward<Args>(args)...)};

        //task_t task {
        //    [callable = std::forward<NonBlockingFunction>(func), arguments = std::make_tuple(std::forward<Args>(args)...) ] () mutable {
        //        return std::apply(callable, std::move(arguments));
        //    }
        //};

		auto fiber_task_ptr = std::make_unique<fiber_task<R>>(
			
			static_cast<typename fiber_task<R>::task_t>(

				[callable = std::forward<FiberFunc>(func), arguments = std::make_tuple(std::forward<Args>(args)...) ] () mutable {
					return std::apply(callable, arguments);
				}

			)

		);

        auto task_future = fiber_task_ptr->callable.get_future();

        task_channel.push(std::move(fiber_task_ptr));

        return task_future;
    }
 
private:

    static constexpr unsigned channel_size = 2048;

    std::vector<std::thread> workers;

    boost::fibers::buffered_channel<std::unique_ptr<task_base>> task_channel {channel_size};
 

    // ?
    // bool stop;
};




}


#endif
