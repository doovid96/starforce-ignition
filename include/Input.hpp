#ifndef INPUT_HPP
#define INPUT_HPP

#include "MVPType.hpp"
#include "EventFlags.hpp"
#include "GuardFlags.hpp"
#include "CatchFlags.hpp"

#include <cstdint>


namespace sf
{


class Input
{

public:

	Input(
		const int32_t equipment_level,
		const int8_t start_star,
		const int8_t goal_star,
		const MVPType mvp,
		const EventFlags event_flags,
		const GuardFlags guard_flags,
		const CatchFlags catch_flags);
	int32_t get_equipment_level() const;
	int8_t get_start() const;
	int8_t get_goal() const;
	MVPType get_mvp() const;
	EventFlags get_events() const;
	GuardFlags get_guards() const;
	CatchFlags get_catches() const;

private:

	int32_t equipment_level;
	int8_t start_star;
	int8_t goal_star;
	MVPType mvp;
	EventFlags event_flags;
	GuardFlags guard_flags;
	CatchFlags catch_flags;

};


}  // namespace sf


#endif