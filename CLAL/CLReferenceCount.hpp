

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

	template <typename T, cl_int(STDCALL *Retain)(T), cl_int(STDCALL *Release)(T)>
	class ReferenceCount {

		using BaseType = ReferenceCount<T, Retain, Release>;


		explicit ReferenceCount(T comp) : component(comp) {
			RetainComponent();
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








