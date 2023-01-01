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

	static constexpr std::size_t MESO_HISTOGRAM_BINS{1'000U};
	static constexpr std::size_t BOOM_HISTOGRAM_BINS{100U};

	friend std::ostream& operator<<(std::ostream& os, const Output& results);

	int64_t iterations{};
	int64_t mesos{};
	int64_t booms{};
	int64_t chance_times{};
	std::array<int64_t, MESO_HISTOGRAM_BINS> meso_histogram{};
	std::array<int64_t, BOOM_HISTOGRAM_BINS> boom_histogram{};
	Output& operator+=(const Output& other);

};


}  // namespace sf

#endif