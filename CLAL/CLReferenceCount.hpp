

#ifndef _CLAL_CLREFERENCECOUNT_HPP_
#define _CLAL_CLREFERENCECOUNT_HPP_


#ifdef WIN32
#define STDCALL __stdcall
#include <CL/cl.h>
#else
#define STDCALL
#include <CL/cl.h>
#endif


namespace CLAL {

	// Base class for all the OpenCL components
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

		ReferenceCount(const BaseType& rhs) : component(rhs.component) {
			RetainComponent();
		}

		BaseType& operator= (const BaseType& rhs) {

			if (&rhs != this) {
				ReleaseComponent();

				component = rhs.component;
				RetainComponent();

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



}





#endif








