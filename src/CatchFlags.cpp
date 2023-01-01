#include "CatchFlags.hpp"


namespace sf
{


std::ostream& operator<<(std::ostream& os, const CatchFlags& catch_flags)
{
	for (std::size_t star{}; star < catch_flags.flags.size(); ++star)
	{
		os << star << ' ' << static_cast<int>(catch_flags.flags.test(star)) << '\n';
	}
	return os;
}


CatchFlags::CatchFlags(std::initializer_list<int8_t> list)
{
	for (const int8_t star : list)
	{
		flags.set(star);
	}
}

CatchFlags::CatchFlags(const Flags flag)
{
	if (flag == Flags::ALL)
	{
		flags = 0x1FFFFFFU;
	}
}


bool CatchFlags::operator[](const int8_t star)
{
	return flags.test(star);
}


}  // namespace sf