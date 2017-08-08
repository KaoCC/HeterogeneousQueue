#ifndef _CLAL_CLPARAMETER_HPP_
#define _CLAL_CLPARAMETER_HPP_



#ifdef __APPLE__
#include <OpenCL/OpenCL.h>
#else
#include <CL/cl.h>
#endif


namespace CLAL {

	class Parameter {

	public:

		enum Type {
			kInt,
			kUInt,
			kFloat,
			kFloat2,
			kFloat4,
			kDouble,
			kMem
		};

		// helper function
		static void setArg(cl_kernel kernel, unsigned int idx, const Parameter& param);

		Parameter(cl_int intVal) : intValue(intVal), type(kInt) {}
		Parameter(cl_uint uintVal) : uintValue(uintVal), type(kUInt) {}
		Parameter(cl_float floatVal) : floatValue(floatVal), type(kFloat) {}
		Parameter(cl_float2 floatVal) : floatValue2(floatVal), type(kFloat2) {}
		Parameter(cl_float4 floatVal) : floatValue4(floatVal), type(kFloat4) {}
		Parameter(cl_double doubleVal) : doubleValue(doubleVal), type(kDouble) {}
		Parameter(cl_mem  mem) : memObject(mem), type(kMem) {}

	private:

		Type type;

		// save the space
		union {
			cl_int intValue;
			cl_uint uintValue;
			cl_float floatValue;
			cl_float2 floatValue2;
			cl_float4 floatValue4;
			cl_double doubleValue;
			cl_mem memObject;
		};

	};

}





#endif
