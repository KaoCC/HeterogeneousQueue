
#ifndef _CE_DEVICESEQUENTIAL_HPP_
#define _CE_DEVICESEQUENTIAL_HPP_

#include "Device.hpp"

namespace CE {


	class DeviceSequential : public Device {

	public:

		// Inherited via Device
		virtual DeviceSpec getSpec(void) override;
		virtual PlatformType getPlatformType() const override;
		virtual Buffer * createBuffer(size_t size, size_t flags) override;
		virtual Buffer * createBuffer(size_t size, size_t flags, void * data) override;
		virtual void deleteBuffer(Buffer * buffer) override;
		virtual Executable * compileExecutable(char const * source_code, size_t size, char const * options) override;
		virtual CE::Event* execute(Function const * func, size_t queue, size_t global_size, size_t local_size, Event** e) override;



		// Inherited via Device
		virtual void readBuffer(Buffer const * buffer, size_t queue, size_t offset, size_t size, void * dst, Event ** e) const override;
		virtual void writeBuffer(Buffer const * buffer, size_t queue, size_t offset, size_t size, void * src, Event ** e) override;

		virtual void deleteExecutable(Executable * executable) override;

		virtual void waitForEvent(Event * e) override;

		virtual void flush(size_t queue) override;
		virtual void finish(size_t queue) override;







		// Sequential
		Executable * createExecutable();

		// members ?



		// Inherited via Device
		virtual Executable * compileExecutable(char const * fileName, char const ** headerNames, size_t numheaders, char const * options) override;


		// Inherited via Device
		virtual void mapBuffer(Buffer const * buffer, size_t queue, size_t offset, size_t size, size_t map_type, void ** mapdata, Event ** e) override;
		virtual void unmapBuffer(Buffer const * buffer, size_t queue, void * mapdata, Event ** e) override;

	};


}







#endif