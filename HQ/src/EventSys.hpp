
#ifndef _HQ_EVENTSYS_HPP_
#define _HQ_EVENTSYS_HPP_


#include <condition_variable>
#include <mutex>

#include "HQ.hpp"


namespace HQ {

	class EventSys : public Event {

	public:

		EventSys(unsigned long cnt = 0);

		void wait() override;
		void signal() override;
		virtual bool isComplete() const override;

	private:

		std::mutex localMutex;
		std::condition_variable localCondition;
		unsigned long count{ 0 };

	};

}












#endif