
#ifndef _CE_DEVICESEQUENTIAL_HPP_
#define _CE_DEVICESEQUENTIAL_HPP_

#include "Device.hpp"

namespace CE {


	class DeviceSequential : public Device {

	public:

		// Inherited via Device
		virtual void GetSpec(DeviceSpec & spec) override;
		virtual Platform GetPlatform() const override;
		virtual Buffer * createBuffer(size_t size, size_t flags) override;
		virtual Buffer * createBuffer(size_t size, size_t flags, void * data) override;
		virtual void deleteBuffer(Buffer * buffer) override;
		virtual Executable * compileExecutable(char const * source_code, size_t size, char const * options) override;
		virtual void execute(Function const * func, size_t queue, size_t global_size, size_t local_size) override;



		// members ?

	};


}







#endif