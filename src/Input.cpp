#include "Input.hpp"


namespace sf
{


Input::Input(
	const int32_t equipment_level,
	const int8_t start_star,
	const int8_t goal_star,
	const MVPType mvp,
	const EventFlags event_flags,
	const GuardFlags guard_flags,
	const CatchFlags catch_flags)
	: equipment_level{equipment_level}
	, start_star{start_star}
	, goal_star{goal_star}
	, mvp{mvp}
	, event_flags{event_flags}
	, guard_flags{guard_flags}
	, catch_flags{catch_flags}
{}


int32_t Input::get_equipment_level() const
{
	return equipment_level;
}


int8_t Input::get_start() const
{
	return start_star;
}


int8_t Input::get_goal() const
{
	return goal_star;
}


MVPType Input::get_mvp() const
{
	return mvp;
}


EventFlags Input::get_events() const
{
	return event_flags;
}


GuardFlags Input::get_guards() const
{
	return guard_flags;
}


CatchFlags Input::get_catches() const
{
	return catch_flags;
}


}  // namespace sf