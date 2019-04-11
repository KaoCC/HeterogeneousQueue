

#include <iostream>
#include <thread>
#include <vector>

#include "hq/heterogeneous_queue.hpp"

#include <boost/compute/algorithm/copy.hpp>
#include <boost/compute/container/vector.hpp>





int test_function(int id, int number, 
    const std::vector<int>& host_vector, boost::compute::vector<int>& device_vector, 
    boost::compute::command_queue& queue) {

    // std::cout << "Hello : " << id << " " <<  number << " " << std::endl;

    boost::fibers::promise<int> fiber_promise;
    boost::fibers::future<int> fiber_future { fiber_promise.get_future() };

    boost::compute::copy_async(
        host_vector.begin(), host_vector.end(), device_vector.begin(), queue
    ).then(
        [&fiber_promise, id, number](){ 
            // std::cout << id << " " << number << " async copy completed, promise set !!! \n"; 
            fiber_promise.set_value(number);
        }
    );


    queue.flush();

	//std::cout << "launched async copy: " << id << " " << number << std::endl;

	int ret = fiber_future.get();

    // enqueue write

    // enqueue_nd_range_kernel

    // enqueue read    
   

	// std::cout << "After : " << id << " " <<  number << " " << std::endl;

	return ret;
}


void opencl_kernel_test() {


}


class fiber_callable : public hq::nonblocking_callable {
public:
    template<class NonBlockingFunction, class... Args>
    int operator()(NonBlockingFunction&& func, Args&&... args) {
        return func(args...);
    }

    ~fiber_callable() = default;
};



int main() {


    std::cout << "Start Testing HQ\n";

    hq::heterogeneous_queue hqueue;

    std::vector<std::thread> ths;

    int max_num = std::thread::hardware_concurrency() / 2;

    if (max_num <= 0) {
        max_num = 2;
    }


    // create data array on host
    std::vector<int> host_vec(20000000);
    std::iota(host_vec.begin(), host_vec.end(), 0);

    std::cout << max_num << std::endl;

    for (int id = 0; id < max_num; ++id) {

        std::cout << "id : " << id << std::endl;

        ths.push_back( std::thread( [id, &hqueue, &host_vec] {

                    // get default device and setup context
                    boost::compute::device device = boost::compute::system::default_device();

                    std::cout << device.name() << std::endl;

                    boost::compute::context context(device);
                    boost::compute::command_queue queue(context, device);

                    // create vector on device
                    boost::compute::vector<int> device_vector(host_vec.size(), context);

                    std::vector<boost::fibers::future<int>> futures;


					constexpr int ss = 32;

                    for (int i = 0 ; i < ss; ++i) {
						futures.emplace_back(hqueue.enqueue<int>(fiber_callable(), test_function, id, i, host_vec, device_vector, queue));
						std::cout << "+++ enqueue " << id << " " << i << std::endl;
                    }


                    std::cout << "*** Enqueued: " << id << std::endl;

					std::vector<boost::fibers::fiber> work_fibers;

					for (int i = 0; i < ss; ++i) {
						work_fibers.emplace_back([&, i, id]() {
							int result = futures[i].get();
							std::cout << " ------ " << id << " " << result << " Completed -------- !" << std::endl;
						});
					}

					std::cout << " fiber gathering " << id << std::endl;

					std::for_each(std::begin(work_fibers), std::end(work_fibers), std::mem_fn(&boost::fibers::fiber::join));

                    std::cout << " --- > Thread " << id << " Done" << std::endl;
                    
                }
            )
        );
    }

    std::cout << "Task launched\n";

    for (auto&& t : ths) {
        t.join();
    }

    std::cout << "All Done\n";


    return 0;
}


