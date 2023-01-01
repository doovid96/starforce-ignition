#ifndef GUARDFLAGS_HPP
#define GUARDFLAGS_HPP

#include "Flags.hpp"

#include <iostream>
#include <cstdint>
#include <bitset>


namespace sf
{


class GuardFlags
{

	friend std::ostream& operator<<(std::ostream& os, const GuardFlags& guard_flags);
	static constexpr int8_t offset{-12}; // star to index

public:

	explicit GuardFlags(std::initializer_list<int8_t> list);
	explicit GuardFlags(const Flags flag);
	bool operator[](const int8_t star);

private:

	std::bitset<5> flags{};

};


}  // namespace sf


#endif