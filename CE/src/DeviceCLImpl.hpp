
#ifndef _CE_DEVICECLIMPL_HPP_
#define _CE_DEVICECLIMPL_HPP_


#include "DeviceCL.hpp"
#include "CLContext.hpp"
#include "CLDevice.hpp"

namespace CE {

	class DeviceCLImpl : public DeviceCL {

	public:


		// Inherited via DeviceCL
		virtual void getSpec(DeviceSpec & spec) override;
		virtual Platform getPlatform() const override;
		virtual Buffer * createBuffer(size_t size, size_t flags) override;
		virtual Buffer * createBuffer(size_t size, size_t flags, void * data) override;
		virtual void deleteBuffer(Buffer * buffer) override;
		virtual Executable * compileExecutable(char const * source, size_t size, char const * options) override;
		virtual void execute(Function const * func, size_t queue, size_t globalSize, size_t localSize) override;


		virtual Buffer * createBuffer(cl_mem buffer) override;





		// Inherited via DeviceCL
		virtual void readBuffer(Buffer const * buffer, size_t queue, size_t offset, size_t size, void * dst, Event ** e) const override;
		virtual void writeBuffer(Buffer const * buffer, size_t queue, size_t offset, size_t size, void * src, Event ** e) override;

		virtual void deleteExecutable(Executable * executable) override;
		virtual void waitForEvent(Event * e) override;
		virtual void flush(size_t queue) override;
		virtual void finish(size_t queue) override;



	private:

		CLAL::CLContext context;
		CLAL::CLDevice device;

	};

}










#endif
