#ifndef EVENTTYPE_HPP
#define EVENTTYPE_HPP

#include <cstdint>


namespace sf
{


enum class EventType : int8_t
{
	NONE,
	DISCOUNT,
	PASS,
	SHINING
};


}  // namespace sf

#endif