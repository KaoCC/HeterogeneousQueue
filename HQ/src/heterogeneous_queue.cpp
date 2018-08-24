

#include "heterogeneous_queue.hpp"
#include <boost/compute/core.hpp>

// test
#include <iostream>

namespace hq {

heterogeneous_queue::heterogeneous_queue() {

    auto selected_platform = boost::compute::system::platforms()[0];

    devices = selected_platform.devices();

    for (const auto& device : devices) {

        std::cout << "hello from " << device.name();
        std::cout << " (platform: " << device.platform().name() << ")" << std::endl;


        auto current_context = boost::compute::context(device);

        contexts.emplace_back(current_context);
        queues.emplace_back(boost::compute::command_queue(current_context, device));
    }

    



}

heterogeneous_queue::~heterogeneous_queue() {

}



}


