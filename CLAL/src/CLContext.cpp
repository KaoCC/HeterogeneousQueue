#include "CLContext.hpp"
#include "CLCommandQueue.hpp"
#include "CLDevice.hpp"
#include "CLCommandQueue.hpp"
#include "CLProgram.hpp"

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
		cl_context ctx = clCreateContext(props, static_cast<cl_int>(deviceIDs.size()), deviceIDs.data(), nullptr, nullptr, &status);


		// Throw ?

		CLContext retContext(ctx, devices);
		clReleaseContext(ctx);

		return retContext;
	}



	CLContext CLContext::create(cl_context context, cl_device_id * primDeviecs, cl_command_queue * primCQs, size_t numDevices) {

		std::vector<CLDevice> localDevices;
		std::vector<CLCommandQueue> localCQs;

		for (size_t i = 0; i < numDevices; ++i) {
			// KAOCC: check if they are moveable !!
			localDevices[i] = CLDevice::create(primDeviecs[i]);
			localCQs[i] = CLCommandQueue::create(primCQs[i]);
		}

		return CLContext::CLContext(context, localDevices, localCQs);
	}

	size_t CLContext::getDeviceCount() const {
		return devices.size();
	}

	CLDevice CLContext::getDevice(size_t index) const {

		// KAOCC: lazy binding or throw ?
		return devices[index];
	}




	CLProgram CLContext::createProgram(const std::vector<char>& sourceCode, char const * buildOpts) const {
		return CLProgram::createFromSource(*this, sourceCode.data(), sourceCode.size(), buildOpts);
	}

	CLEvent CLContext::execute1D(unsigned int index, size_t globalSize, size_t localSize, cl_kernel kernel) {

		cl_event event = nullptr;

		cl_int status = clEnqueueNDRangeKernel(commandQueues[index], kernel, 1, nullptr, &globalSize, &localSize, 0, nullptr, &event);
		ThrowIfCL(status != CL_SUCCESS, status, "clEnqueueNDRangeKernel failed");

		return CLEvent::create(event);

	}

	CLEvent CLContext::execute1D(unsigned int index, size_t globalSize, size_t localSize, cl_kernel kernel, CLEvent depEvent) {

		cl_event event = nullptr;
		cl_event eventToWait = depEvent;

		cl_int status = clEnqueueNDRangeKernel(commandQueues[index], kernel, 1, nullptr, &globalSize, &localSize, 0, &eventToWait, &event);
		ThrowIfCL(status != CL_SUCCESS, status, "clEnqueueNDRangeKernel failed");

		return CLEvent::create(event);
	}

	void CLContext::finish(size_t index) {
		cl_int status = clFinish(commandQueues[index]);
		ThrowIfCL(status != CL_SUCCESS, status, "clFinish failed");
	}

	void CLContext::flush(size_t index) {
		cl_int status = clFlush(commandQueues[index]);
		ThrowIfCL(status != CL_SUCCESS, status, "clFlush failed");
	}

	CLCommandQueue CLContext::getCommandQueue(size_t index) const {

		// KAOCC: lazy binding or throw exception

		return commandQueues[index];
	}

	CLContext::~CLContext() {
	}

	//CLContext::CLContext(cl_context context, const std::vector<CLDevice>& devs) : 
	//	ReferenceCount<cl_context, clRetainContext, clReleaseContext>(context)
	//	, devices(devs) {

	//	// KAOCC:
	//	// Init CQs

	//	createCQs();

	//}


	// Copy by value !
	CLContext::CLContext(cl_context context, std::vector<CLDevice> devs) :
		ReferenceCount<cl_context, clRetainContext, clReleaseContext>(context)
		, devices(std::move(devs)) {

		createCQs();
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
