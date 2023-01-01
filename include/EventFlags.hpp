#ifndef EVENTFLAGS_HPP
#define EVENT_FLAGS_HPP

#include "EventType.hpp"

#include <iostream>
#include <cstdint>
#include <initializer_list>


namespace sf
{


class EventFlags
{

	friend std::ostream& operator<<(std::ostream& os, const EventFlags& event_flags);

public:

	explicit EventFlags(std::initializer_list<EventType> event_list);
	bool get_discount() const;
	bool get_pass() const;

private:

	bool discount{};
	bool pass{};

};


}  // namespace sf

#endif