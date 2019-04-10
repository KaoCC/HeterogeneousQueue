

#include <iostream>
#include <thread>
#include <vector>

#include "hq/heterogeneous_queue.hpp"

#include <boost/compute/algorithm/copy.hpp>
#include <boost/compute/container/vector.hpp>





void test_function(int id, int number, 
    const std::vector<int>& host_vector, boost::compute::vector<int>& device_vector, 
    boost::compute::command_queue& queue) {

    std::cout << "Hello : " << id << " " <<  number << " " << std::endl;

    boost::fibers::promise<void> fiber_promise;
    boost::fibers::future<void> fiber_future { fiber_promise.get_future() };

    boost::compute::copy_async(
        host_vector.begin(), host_vector.end(), device_vector.begin(), queue
    ).then(
        [&fiber_promise, id, number](){ 
            std::cout << id << " " << number << " async copy completed, promise set !!! \n"; 
            fiber_promise.set_value();
        }
    );

    std::cout << "launched async copy" << std::endl;


    queue.flush();

    fiber_future.get();

    // enqueue write

    // enqueue_nd_range_kernel

    // enqueue read    
    

    std::cout << "After : " << id << " " <<  number << " " << std::endl;
}


void opencl_kernel_test() {


}


class fiber_callable : public hq::nonblocking_callable {
public:
    template<class NonBlockingFunction, class... Args>
    void operator()(NonBlockingFunction&& func, Args&&... args) {
        func(args...);
    }

    ~fiber_callable() = default;
};



int main() {


    std::cout << "Start Testing HQ\n";

    hq::heterogeneous_queue<void> hqueue;

    std::vector<std::thread> ths;

    int max_num = std::thread::hardware_concurrency() - 1;

    if (max_num <= 0) {
        max_num = 2;
    }

    // create data array on host
    std::vector<int> host_vec(30000000);
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

                    std::vector<hq::heterogeneous_queue<void>::future_t> futures;

                    for (int i = 0 ; i < 32; ++i) {
                        futures.push_back(hqueue.enqueue(fiber_callable(), test_function, id, i, host_vec, device_vector, queue));
                    }

                    // queue.flush();

                    std::cout << "Enqueued: " << id << std::endl;

                    for (auto&& fu : futures) {
                        fu.get();
                    }

                    std::cout << "Thread " << id << " Done" << std::endl;
                    
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


