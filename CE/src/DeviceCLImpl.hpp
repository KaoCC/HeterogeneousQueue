
#ifndef _CE_DEVICECLIMPL_HPP_
#define _CE_DEVICECLIMPL_HPP_


#include "DeviceCL.hpp"
#include "CLContext.hpp"
#include "CLDevice.hpp"

namespace CE {

	class DeviceCLImpl : public DeviceCL {
		// Inherited via DeviceCL
		virtual void GetSpec(DeviceSpec & spec) override;
		virtual Platform GetPlatform() const override;
		virtual Buffer * createBuffer(size_t size, size_t flags) override;
		virtual Buffer * createBuffer(size_t size, size_t flags, void * data) override;
		virtual void deleteBuffer(Buffer * buffer) override;
		virtual Executable * compileExecutable(char const * source_code, size_t size, char const * options) override;
		virtual void execute(Function const * func, size_t queue, size_t global_size, size_t local_size) override;
		virtual Buffer * createBuffer(cl_mem buffer) override;



	private:

		CLAL::CLContext context;
		CLAL::CLDevice device;


	};

}










#endif
