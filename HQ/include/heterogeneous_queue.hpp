
#ifndef _HQ_HETEROGENEOUS_QUEUE_HPP_
#define _HQ_HETEROGENEOUS_QUEUE_HPP_

#include <vector>
#include <thread>
#include <boost/compute/core.hpp> 

namespace hq {



class heterogeneous_queue {

public:
    heterogeneous_queue();
    ~heterogeneous_queue();

    heterogeneous_queue(const heterogeneous_queue&) = delete;
    heterogeneous_queue& operator=(const heterogeneous_queue&) = delete;

 
private:

    

    std::vector<boost::compute::device> devices;
    std::vector<boost::compute::context> contexts;
    std::vector<boost::compute::command_queue> queues;

    std::vector<std::thread> workers;
};




}


#endif