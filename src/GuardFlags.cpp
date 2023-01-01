#include "GuardFlags.hpp"


namespace sf
{


std::ostream& operator<<(std::ostream& os, const GuardFlags& guard_flags)
{
	for (std::size_t star{12}; star < 12 + guard_flags.flags.size(); ++star)
	{
		os << star << ' ' << static_cast<int>(guard_flags.flags.test(star + GuardFlags::offset)) << '\n';
	}
	return os;
}


GuardFlags::GuardFlags(std::initializer_list<int8_t> list)
{
	for (const int8_t star : list)
	{
		flags.set(star + offset);
	}
}

GuardFlags::GuardFlags(const Flags flag)
{
	if (flag == Flags::ALL)
	{
		flags = 0x1FU;
	}
}


bool GuardFlags::operator[](const int8_t star)
{
	return flags.test(star + offset);
}


}  // namespace sf