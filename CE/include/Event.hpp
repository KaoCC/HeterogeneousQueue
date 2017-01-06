#ifndef _CE_EVENT_HPP
#define _CE_EVENT_HPP

#include "CE_common.hpp"

namespace CE {

	class CE_API Event {

	public:

		Event() = default;

		virtual void wait() = 0;
		virtual bool isComplete() const = 0;

		virtual ~Event() = default;


		Event(Event const&) = delete;
		Event& operator = (Event const&) = delete;
	};

}




#endif