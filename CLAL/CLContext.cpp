#include "CLContext.hpp"
#include "CLCommandQueue.hpp"

#include <algorithm>

namespace CLAL {

	CLContext CLContext::create(const std::vector<CLDevice>& devices, cl_context_properties * props) {




		std::vector<cl_device_id> deviceIDs;


		std::for_each(devices.cbegin(), devices.cend(),
			[&deviceIDs](CLDevice const& device)
		{
			deviceIDs.push_back(device);
		});


		cl_int status = CL_SUCCESS;


		cl_context ctx = clCreateContext(props, devices.size(), deviceIDs.data(), nullptr, nullptr, &status);


		// Throw ?


		CLContext retContext(ctx, devices);

		clReleaseContext(ctx);

		return retContext;
	}



	CLContext CLContext::create(cl_context context, cl_device_id * primDeviecs, cl_command_queue * primCQs, int numDevices) {

		std::vector<CLDevice> localDevices;
		std::vector<CLCommandQueue> localCQs;

		for (size_t i = 0; i < numDevices; ++i) {
			localDevices[i] = CLDevice::create(primDeviecs[i]);
			localCQs[i] = CLCommandQueue::create(primCQs[i]);
		}

		return CLContext::CLContext(context, localDevices, localCQs);
	}




	CLCommandQueue CLContext::getCommandQueue(size_t index) {

		// KAOCC: lazy binding or throw exception

		return commandQueues[index];
	}

	CLContext::~CLContext() {
	}

	CLContext::CLContext(cl_context context, const std::vector<CLDevice>& devs) : 
		ReferenceCount<cl_context, clRetainContext, clReleaseContext>(context)
		, devices(devs) {

		// KAOCC:
		// More here !

	}

	void CLContext::createCQs() {


		std::for_each(devices.cbegin(), devices.cend(), 
			[this](const CLDevice& dev ) {

			// KAOCC: ERROR: need CLCommandQueue(CLDevice, CLContext);
			// FIXED 
			commandQueues.push_back(CLCommandQueue::create(dev, *this));

		});


	}

}
