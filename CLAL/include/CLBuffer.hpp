
#ifndef _CLAL_CLBUFFER_HPP_
#define _CLAL_CLBUFFER_HPP_

#include "CLReferenceCount.hpp"
#include "CLEvent.hpp"
#include "CLCommandQueue.hpp"
#include "CLParameter.hpp"

namespace CLAL {

	template <typename T>
	class CLBuffer : public ReferenceCount<cl_mem, clRetainMemObject, clReleaseMemObject> {


	public:

		static CLBuffer<T> createFromBufferCL(cl_mem buffer);
		static CLBuffer<T> create(cl_context context, cl_mem_flags flags, size_t elementCount);
		static CLBuffer<T> create(cl_context context, cl_mem_flags flags, size_t elementCount, void* data);


		// Read and Write
		CLEvent writeDeviceBuffer(CLCommandQueue cmdQueue, T const* hostBuffer, size_t elemCount);
		CLEvent writeDeviceBuffer(CLCommandQueue cmdQueue, T const* hostBuffer, size_t offset, size_t elemCount);
		CLEvent readDeviceBuffer(CLCommandQueue cmdQueue, T* hostBuffer, size_t elemCount);
		CLEvent readDeviceBuffer(CLCommandQueue cmdQueue, T* hostBuffer, size_t offset, size_t elemCount);

		// Map / Unmap buffer
		CLEvent mapDeviceBuffer(CLCommandQueue cmdQueue, cl_map_flags flags, T** mappedData);
		CLEvent mapDeviceBuffer(CLCommandQueue cmdQueue, cl_map_flags flags, size_t offset, size_t elemCount, T** mappedData);
		CLEvent unmapDeviceBuffer(CLCommandQueue cmdQueue, T* mappedData);




		size_t getElementCount() const;


		// convert to Parameter
		operator Parameter() const {
			// cast to type cl_mem
			return Parameter(static_cast<cl_mem>(*this));
		}

		virtual ~CLBuffer();

	private:

		// wrap cl_mem
		CLBuffer(cl_mem buffer, size_t eleCount);

		size_t elementCount;

	};




	template<typename T>
	CLBuffer<T> CLBuffer<T>::createFromBufferCL(cl_mem buffer) {


		// Get the size
		size_t bufferSize = 0;
		cl_int status = clGetMemObjectInfo(buffer, CL_MEM_SIZE, sizeof(bufferSize), &bufferSize, nullptr);
		ThrowIfCL(status != CL_SUCCESS, status, "clGetMemObjectInfo failed");

		return CLBuffer(buffer, bufferSize / sizeof(T));
	}

	template<typename T>
	CLBuffer<T> CLBuffer<T>::create(cl_context context, cl_mem_flags flags, size_t elementCount) {

		cl_int status = CL_SUCCESS;
		cl_mem deviceBuffer = clCreateBuffer(context, flags, elementCount * sizeof(T), nullptr, &status);

		ThrowIfCL(status != CL_SUCCESS, status, "clCreateBuffer failed");

		CLBuffer<T> buffer(deviceBuffer, elementCount);

		clReleaseMemObject(deviceBuffer);

		return buffer;
	}


	template<typename T>
	CLBuffer<T> CLBuffer<T>::create(cl_context context, cl_mem_flags flags, size_t elementCount, void * data) {


		cl_int status = CL_SUCCESS;

		// KAOCC: TODO: check the flag !
		cl_mem deviceBuffer = clCreateBuffer(context, flags | CL_MEM_COPY_HOST_PTR, elementCount * sizeof(T), data, &status);

		ThrowIfCL(status != CL_SUCCESS, status, "clCreateBuffer failed");

		CLBuffer<T> buffer(deviceBuffer, elementCount);

		clReleaseMemObject(deviceBuffer);

		return buffer;

	}

	//template<typename T>
	//CLEvent CLBuffer<T>::writeDeviceBuffer(CLCommandQueue cmdQueue, T const * hostBuffer, size_t elemCount) {

	//	cl_event event = nullptr;
	//	cl_int status = clEnqueueWriteBuffer(cmdQueue, *this, false, 0, sizeof(T) * elemCount, hostBuffer, 0, nullptr, &event);

	//	ThrowIfCL(status != CL_SUCCESS, status, "clEnqueueWriteBuffer failed");

	//	return CLEvent::create(event);
	//}



	template<typename T>
	CLEvent CLBuffer<T>::writeDeviceBuffer(CLCommandQueue cmdQueue, T const * hostBuffer, size_t offset, size_t elemCount) {

		cl_event event = nullptr;
		cl_int status = clEnqueueWriteBuffer(cmdQueue, *this, false, sizeof(T) * offset, sizeof(T) * elemCount, hostBuffer, 0, nullptr, &event);

		ThrowIfCL(status != CL_SUCCESS, status, "clEnqueueWriteBuffer (offset) failed");

		return CLEvent::create(event);
	}

	template<typename T>
	CLEvent CLBuffer<T>::writeDeviceBuffer(CLCommandQueue cmdQueue, T const * hostBuffer, size_t elemCount) {

		return writeDeviceBuffer(cmdQueue, hostBuffer, 0, elemCount);
	}



	//template<typename T>
	//CLEvent CLBuffer<T>::readDeviceBuffer(CLCommandQueue cmdQueue, T * hostBuffer, size_t elemCount) {

	//	cl_event event = nullptr;
	//	cl_int status = clEnqueueReadBuffer(cmdQueue, *this, false, 0, sizeof(T) * elemCount, hostBuffer, 0, nullptr, &event);

	//	ThrowIfCL(status != CL_SUCCESS, status, "clEnqueueWriteBuffer failed");

	//	return CLEvent::create(event);
	//}



	template<typename T>
	CLEvent CLBuffer<T>::readDeviceBuffer(CLCommandQueue cmdQueue, T * hostBuffer, size_t elemCount) {

		return readDeviceBuffer(cmdQueue, hostBuffer, 0, elemCount);
	}


	template<typename T>
	CLEvent CLBuffer<T>::readDeviceBuffer(CLCommandQueue cmdQueue, T * hostBuffer, size_t offset, size_t elemCount) {
	
		cl_event event = nullptr;
		cl_int status = clEnqueueReadBuffer(cmdQueue, *this, false, sizeof(T) * offset, sizeof(T) * elemCount, hostBuffer, 0, nullptr, &event);

		ThrowIfCL(status != CL_SUCCESS, status, "clEnqueueWriteBuffer failed");

		return CLEvent::create(event);
	}

	template<typename T>
	CLEvent CLBuffer<T>::mapDeviceBuffer(CLCommandQueue cmdQueue, cl_map_flags flags, T ** mappedData) {

		cl_int status = CL_SUCCESS;
		cl_event event = nullptr;

		T* data = static_cast<T*>(clEnqueueMapBuffer(cmdQueue, *this, false, flags, 0, sizeof(T) * elementCount_, 0, nullptr, &event, &status));
		ThrowIfCL(status != CL_SUCCESS, status, "clEnqueueMapBuffer failed");

		*mappedData = data;

		return CLEvent::create(event);


	}

	template<typename T>
	CLEvent CLBuffer<T>::mapDeviceBuffer(CLCommandQueue cmdQueue, cl_map_flags flags, size_t offset, size_t elemCount, T ** mappedData) {

		cl_int status = CL_SUCCESS;
		cl_event event = nullptr;

		T* data = static_cast<T*>(clEnqueueMapBuffer(cmdQueue, *this, false, flags, sizeof(T) * offset, sizeof(T)*elemCount, 0, nullptr, &event, &status));
		ThrowIfCL(status != CL_SUCCESS, status, "clEnqueueMapBuffer (offset) failed");

		*mappedData = data;

		return CLEvent::create(event);
	}

	template<typename T>
	CLEvent CLBuffer<T>::unmapDeviceBuffer(CLCommandQueue cmdQueue, T * mappedData) {

		cl_event event = nullptr;
		cl_int status = clEnqueueUnmapMemObject(cmdQueue, *this, mappedData, 0, nullptr, &event);
		ThrowIfCL(status != CL_SUCCESS, status, "clEnqueueUnmapMemObject failed");

		return CLEvent::create(event);
	}



	template <typename T>
	size_t CLBuffer<T>::getElementCount() const {
		return this->elementCount;
	}

	template <typename T>
	CLBuffer<T>::~CLBuffer() {
	}

	template<typename T>
	CLBuffer<T>::CLBuffer(cl_mem buffer, size_t eleCount) : ReferenceCount<cl_mem, clRetainMemObject, clReleaseMemObject>(buffer)
		, elementCount(eleCount) {
	}









}


#endif
