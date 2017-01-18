#ifndef _CE_CE_COMMON_HPP_
#define _CE_CE_COMMON_HPP_




#ifndef CE_STATIC_LIBRARY
#ifdef WIN32
#ifdef CE_EXPORT_API
#define CE_API __declspec(dllexport)
#else
#define CE_API __declspec(dllimport)
#endif
#elif defined(__GNUC__)
#ifdef CE_EXPORT_API
#define CE_API __attribute__((visibility ("default")))
#else
#define CE_API
#endif
#endif
#else
#define CE_API
#endif

#include <cstdint>
#include <cstddef>

namespace CE {

	enum PlatformType
	{
		kOpenCL = (1 << 0),
		kVulkan = (1 << 1),
		kMix	= (1 << 2),

		kAny = 0xFF
	};

	enum class DeviceType : std::uint8_t {
		kUnknown,
		kGpu,
		kCpu,
		kAccelerator,
		kSequential
	};


}


#endif









