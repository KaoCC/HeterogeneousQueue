#include "CLParameter.hpp"
#include "CLException.hpp"

namespace CLAL {

	void Parameter::setArg(cl_kernel kernel, unsigned int index, const Parameter& param) {


		cl_int status = CL_SUCCESS;
		switch (param.type) {

		case Parameter::kInt:
			status = clSetKernelArg(kernel, index, sizeof(cl_int), &param.intValue);
			break;

		case Parameter::kUInt:
			status = clSetKernelArg(kernel, index, sizeof(cl_uint), &param.uintValue);
			break;

		case Parameter::kFloat:
			status = clSetKernelArg(kernel, index, sizeof(cl_float), &param.floatValue);
			break;

		case Parameter::kFloat2:
			status = clSetKernelArg(kernel, index, sizeof(cl_float2), &param.floatValue2);
			break;

		case Parameter::kFloat4:
			status = clSetKernelArg(kernel, index, sizeof(cl_float4), &param.floatValue4);
			break;

		case Parameter::kDouble:
			status = clSetKernelArg(kernel, index, sizeof(cl_double), &param.doubleValue);
			break;

		case Parameter::kMem:
			status = clSetKernelArg(kernel, index, sizeof(cl_mem), &param.memObject);
			break;

		default:
			/* Error ?*/
			break;
		}

		// Error checking?
		ThrowIfCL(status != CL_SUCCESS, status, "clSetKernelArg failed");

	}


}
