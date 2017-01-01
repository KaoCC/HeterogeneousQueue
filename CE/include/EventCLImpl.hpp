
#ifndef _CE_EVENTCLIMPL_HPP_
#define _CE_EVENTCLIMPL_HPP_

#include "CLEvent.hpp"
#include "Event.hpp"

namespace CE {


	class EventCLImpl : public Event {



	public:

		// Inherited via Event
		virtual void wait() override;

		virtual bool isComplete() const override;

	private:
		CLAL::CLEvent event;

	};

}










#endif
