#ifndef _CE_DEVICE_HPP_
#define _CE_DEVICE_HPP_


#include "CE_common.hpp"


namespace CE {

	class Buffer;
	class Executable;
	class Function;
	class Event;


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
		bool isThreadSafe;
	};


	class CE_API Device {
	public:


		Device() = default;
		virtual ~Device() = default;

		// Device Properties
		virtual DeviceSpec getSpec(void) = 0;
		virtual PlatformType getPlatformType() const = 0;

		// Buffers
		virtual Buffer* createBuffer(size_t size, size_t flags) = 0;
		virtual Buffer* createBuffer(size_t size, size_t flags, void* data) = 0;
		virtual void deleteBuffer(Buffer* buffer) = 0;

		// Read Write for Buffers (void pointers)
		virtual void readBuffer(Buffer const* buffer, size_t queue, size_t offset, size_t size, void* dst, Event** e) const = 0;
		virtual void writeBuffer(Buffer const* buffer, size_t queue, size_t offset, size_t size, void* src, Event** e) = 0;


		// Executable
		virtual Executable* compileExecutable(char const* source, size_t size, char const* options) = 0;
		virtual Executable* compileExecutable(char const* fileName, char const** headerNames, size_t numheaders, char const* options) = 0;
		virtual void deleteExecutable(Executable* executable) = 0;

		//virtual void execute(Function const* func, size_t queue, size_t global_size, size_t local_size, Event** e) = 0;
		virtual void execute(Function const* func, size_t queue, size_t globalSize, size_t localSize, Event** e) = 0;


		//TODO: add more function here


		// Event 
		virtual void waitForEvent(Event* e) = 0;


		virtual void flush(size_t queue) = 0;
		virtual void finish(size_t queue) = 0;

		// remove copy & assignment
		Device(Device const&) = delete;
		Device& operator = (Device const&) = delete;

	};

	CE_API Executable * CreateSequentialExecutable(Device* device);
	
}



#endif



