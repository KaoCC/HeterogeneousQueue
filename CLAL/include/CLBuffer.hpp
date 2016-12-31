
#ifndef _CLAL_CLBUFFER_HPP_
#define _CLAL_CLBUFFER_HPP_

#include "CLReferenceCount.hpp"


namespace CLAL {

	template <typename T>
	class CLBuffer : public ReferenceCount<cl_mem, clRetainMemObject, clReleaseMemObject> {


	public:

		static CLBuffer<T> createFromBufferCL(cl_mem buffer);
		static CLBuffer<T> create(cl_context context, cl_mem_flags flags, size_t elementCount);


		size_t getElementCount() const;

		virtual ~CLBuffer();

	private:

		// wrap cl_mem
		CLBuffer(cl_mem buffer, size_t elementCount);

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


	template <typename T>
	size_t CLBuffer<T>::getElementCount() const {
		return this->elementCount;
	}

	template <typename T>
	CLBuffer<T>::~CLBuffer() {
	}









}


#endif
