#ifndef OUTPUT_HPP
#define OUTPUT_HPP

#include <iostream>
#include <iomanip>
#include <array>
#include <cstdint>
#include <cstddef>
#include <algorithm>


namespace sf
{


struct Output
{

	friend std::ostream& operator<<(std::ostream& os, const Output& results);

	int64_t iterations{};
	int64_t mesos{};
	int64_t booms{};
	int64_t chance_times{};
	Output& operator+=(const Output& other);

};


}  // namespace sf

#endif