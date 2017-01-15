
#ifndef _CE_DEVICECLIMPL_HPP_
#define _CE_DEVICECLIMPL_HPP_


#include "DeviceCL.hpp"
#include "CLContext.hpp"
#include "CLDevice.hpp"

#include <queue>

namespace CE {

	// KAOCC: NOTE: CL device is not reentry-able
	// CQ has no threading protection

	class EventCLImpl;

	class DeviceCLImpl : public DeviceCL {

	public:


		// ctors 

		DeviceCLImpl(CLAL::CLDevice dev);
		DeviceCLImpl(CLAL::CLDevice dev, CLAL::CLContext ctx);



		// Inherited via DeviceCL
		virtual DeviceSpec getSpec(void) override;
		virtual PlatformType getPlatformType() const override;
		virtual Buffer * createBuffer(size_t size, size_t flags) override;
		virtual Buffer * createBuffer(size_t size, size_t flags, void * data) override;
		virtual void deleteBuffer(Buffer * buffer) override;



		virtual CE::Event* execute(Function const * func, size_t queue, size_t globalSize, size_t localSize, bool eventFlag) override;


		virtual Buffer * createBuffer(cl_mem buffer) override;


		// read / write
		virtual void readBuffer(Buffer const * buffer, size_t queue, size_t offset, size_t size, void * dst, Event ** e) const override;
		virtual void writeBuffer(Buffer const * buffer, size_t queue, size_t offset, size_t size, void * src, Event ** e) override;

		// map / unmap
		virtual void mapBuffer(Buffer const * buffer, size_t queue, size_t offset, size_t size, size_t map_type, void ** mapdata, Event ** e) override;
		virtual void unmapBuffer(Buffer const * buffer, size_t queue, void * mapdata, Event ** e) override;

		virtual Executable * compileExecutable(char const * source, size_t size, char const * options) override;
		virtual Executable * compileExecutable(char const * filename, char const ** headernames, size_t numheaders, char const * options) override;
		virtual void deleteExecutable(Executable * executable) override;



		// KAOCC: we need to redesign this API ...
		virtual void waitForEvent(Event * e) override;


		virtual void flush(size_t queue) override;
		virtual void finish(size_t queue) override;

		~DeviceCLImpl();



	protected:

		// Event Pool Operations
		EventCLImpl* createEventCL() const;
		void releaseEventCL(EventCLImpl* e) const ;


	private:

		// KAOCC: do we need mutex for thread safe ???

		CLAL::CLContext context;
		CLAL::CLDevice device;

		// Event Pool
		void initEventPool();
		static const size_t INIT_EVENT_POOL_SIZE = 10;
		mutable std::queue<EventCLImpl*> eventPool;  // for const member function


		// Mem / data Pool ????

	};

}










#endif
