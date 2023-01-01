#include "EventFlags.hpp"

namespace sf
{


std::ostream& operator<<(std::ostream& os, const EventFlags& event_flags)
{
	return os << "DISCOUNT " << event_flags.discount << "\nPASS " << event_flags.pass << '\n';
}


EventFlags::EventFlags(std::initializer_list<EventType> event_list)
{
	for (EventType event_type : event_list)
	{
		switch(event_type)
		{
		case EventType::NONE:
			discount = false;
			pass = false;
			break;
		case EventType::DISCOUNT:
			discount = true;
			break;
		case EventType::PASS:
			pass = true;
			break;
		case EventType::SHINING:
			discount = true;
			pass = true;
		}
	}
}


bool EventFlags::get_discount() const
{
	return discount;
}


bool EventFlags::get_pass() const
{
	return pass;
}


}  // namespace sf