#ifndef _CE_DEVICE_HPP_
#define _CE_DEVICE_HPP_


#include "CE_common.hpp"


namespace CE {

	class Buffer;
	class Executable;
	class Function;

	class CE_API Device {
	public:


		virtual Buffer* createBuffer(size_t size, size_t flags) = 0;
		virtual Buffer* createBuffer(size_t size, size_t flags, void* data) = 0;
		virtual void deleteBuffer(Buffer* buffer) = 0;



		virtual Executable* compileExecutable(char const* source_code, size_t size, char const* options) = 0;


		//virtual void execute(Function const* func, size_t queue, size_t global_size, size_t local_size, Event** e) = 0;
		virtual void execute(Function const* func, size_t queue, size_t global_size, size_t local_size) = 0;



		virtual ~Device() = 0;

	};

}



#endif



