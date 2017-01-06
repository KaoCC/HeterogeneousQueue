
#ifndef _CE_EVENTCLIMPL_HPP_
#define _CE_EVENTCLIMPL_HPP_

#include "CLEvent.hpp"
#include "Event.hpp"

namespace CE {


	class EventCLImpl : public Event {

	public:

		EventCLImpl();

		~EventCLImpl();

		// Inherited via Event
		virtual void wait() override;

		virtual bool isComplete() const override;


		void setEvent(CLAL::CLEvent evt);


	private:
		CLAL::CLEvent event;

		// to check if it is a valid event instance
		bool validFlag = false;

	};

}










#endif
