#ifndef CATCHFLAGS_HPP
#define CATCHFLAGS_HPP

#include "Flags.hpp"

#include <iostream>
#include <cstdint>
#include <bitset>


namespace sf
{


class CatchFlags
{

	friend std::ostream& operator<<(std::ostream& os, const CatchFlags& guard_flags);

public:

	explicit CatchFlags(std::initializer_list<int8_t> list);
	explicit CatchFlags(const Flags flag);
	bool operator[](const int8_t star);

private:

	std::bitset<25> flags{};

};


}  // namespace sf


#endif