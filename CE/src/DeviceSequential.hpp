
#ifndef _CE_DEVICESEQUENTIAL_HPP_
#define _CE_DEVICESEQUENTIAL_HPP_

#include "Device.hpp"

namespace CE {


	class DeviceSequential : public Device {

	public:

		// Inherited via Device
		virtual void getSpec(DeviceSpec & spec) override;
		virtual Platform getPlatform() const override;
		virtual Buffer * createBuffer(size_t size, size_t flags) override;
		virtual Buffer * createBuffer(size_t size, size_t flags, void * data) override;
		virtual void deleteBuffer(Buffer * buffer) override;
		virtual Executable * compileExecutable(char const * source_code, size_t size, char const * options) override;
		virtual void execute(Function const * func, size_t queue, size_t global_size, size_t local_size) override;



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


	};


}







#endif