

#ifndef _CLAL_CLREFERENCECOUNT_HPP_
#define _CLAL_CLREFERENCECOUNT_HPP_


#ifdef __APPLE__
#define STDCALL
#include <OpenCL/OpenCL.h>
#elif WIN32
#define STDCALL __stdcall
#include <CL/cl.h>
#else
#define STDCALL
#include <CL/cl.h>
#endif


namespace CLAL {

	// Base class (Wrapper) for all the OpenCL components
	// assume that T is a pointer type for CL
	template <typename T, cl_int(STDCALL *Retain)(T), cl_int(STDCALL *Release)(T)>
	class ReferenceCount {


	public:

		using BaseType = ReferenceCount<T, Retain, Release>;

		ReferenceCount() : component(nullptr) {

		}

		explicit ReferenceCount(T comp) : component(comp) {
			RetainComponent();
		}

		// copy
		ReferenceCount(const BaseType& rhs) : component(rhs.component) {
			RetainComponent();
		}

		// assignment
		BaseType& operator= (const BaseType& rhs) {

			if (&rhs != this) {
				ReleaseComponent();

				component = rhs.component;
				RetainComponent();

			}

			return *this;
		}

		// move assignment ?
		BaseType& operator= (BaseType&& rhs) {

			if (&rhs != this) {
				// Release what we had before
				ReleaseComponent();

				// Steal the component from rhs !
				component = rhs.component;
				//RetainComponent();  // no need !!!

				// Set rhs to default state
				//rhs.ReleaseComponent();  // no need !!!
				rhs.component = nullptr;

			}

			return *this;
		}

		// convert
		operator T() const {
			return component;
		}


		~ReferenceCount() {
			ReleaseComponent();
		}


	private:
		void RetainComponent() {
			if (component)
				Retain(component);
		}

		void ReleaseComponent() {
			if (component)
				Release(component);
		}

		// OpenCL Component
		T component;
	};






	// for OpenCL platform
	template<>
	class ReferenceCount<cl_platform_id, nullptr, nullptr> {

	public:
		using BaseType = ReferenceCount<cl_platform_id, nullptr, nullptr>;


		ReferenceCount() : platform(nullptr) {

		}

		explicit ReferenceCount(cl_platform_id plat) : platform(plat) {
		}


		// copy
		ReferenceCount(const BaseType& rhs) : platform(rhs.platform) {
		}


		// assignment
		BaseType& operator= (const BaseType& rhs) {

			if (&rhs != this) {
				platform = rhs.platform;
			}

			return *this;
		}


		//convert
		operator cl_platform_id() const {
			return platform;
		}


		~ReferenceCount() {
		}


	private:

		cl_platform_id platform;
	};




}





#endif








