#ifndef _CE_EVENTSEQUENTIALUMPL_HPP_
#define _CE_EVENTSEQUENTIALUMPL_HPP_

#include "Event.hpp"

#include <future>

namespace CE {


	class EventSequentialImpl : public Event {
	public:

		EventSequentialImpl(std::future<void>& fu);
		~EventSequentialImpl() = default;

		// Inherited via Event
		virtual void wait() override;

		virtual bool isComplete() const override;

	private:


		std::future<void> mFuture;

	};







}












#endif

