#ifndef _CE_DEVICE_HPP_
#define _CE_DEVICE_HPP_


#include "CE_common.hpp"


namespace CE {

	class Buffer;
	class Executable;
	class Function;



	//struct DeviceSpec {
	//	char const* name;
	//	char const* vendor;

	//	DeviceType  type;
	//	SourceType  sourceTypes;

	//	size_t min_alignment;
	//	size_t max_num_queues;

	//	size_t global_mem_size;
	//	size_t local_mem_size;
	//	size_t max_alloc_size;
	//	size_t max_local_size;
	//};

	struct DeviceSpec {
		const char* name;
		const char* vendor;
		DeviceType  type;
	};


	class CE_API Device {
	public:


		Device() = default;
		virtual ~Device() = default;

		// Device Properties
		virtual void GetSpec(DeviceSpec& spec) = 0;
		virtual Platform GetPlatform() const = 0;

		virtual Buffer* createBuffer(size_t size, size_t flags) = 0;
		virtual Buffer* createBuffer(size_t size, size_t flags, void* data) = 0;
		virtual void deleteBuffer(Buffer* buffer) = 0;



		virtual Executable* compileExecutable(char const* source_code, size_t size, char const* options) = 0;


		//virtual void execute(Function const* func, size_t queue, size_t global_size, size_t local_size, Event** e) = 0;
		virtual void execute(Function const* func, size_t queue, size_t global_size, size_t local_size) = 0;


		//TODO: add more function here


		// remove copy & assignment
		Device(Device const&) = delete;
		Device& operator = (Device const&) = delete;

	};

	CE_API Executable * CreateSequentialExecutable(Device* device);
	
}



#endif



