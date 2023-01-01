#include "Output.hpp"

namespace sf
{


Output& Output::operator+=(const Output& other)
{
	iterations += other.iterations;
	mesos += other.mesos;
	booms += other.booms;
	chance_times += other.chance_times;
	std::transform(
		meso_histogram.cbegin(), meso_histogram.cend(), other.meso_histogram.cbegin(),
		meso_histogram.begin(), std::plus<int64_t>());
	std::transform(
		boom_histogram.cbegin(), boom_histogram.cend(), other.boom_histogram.cbegin(),
		boom_histogram.begin(), std::plus<int64_t>());
	return *this;
}


std::ostream& operator<<(std::ostream& os, const Output& output)
{
	os << "Iterations: " << output.iterations << '\n';
	os << "Mesos: " << std::fixed << output.mesos / static_cast<double>(output.iterations) << '\n';
	os << "Booms: " << std::fixed << output.booms / static_cast<double>(output.iterations) << '\n';
	os << "Chance Times: " << std::fixed << output.chance_times / static_cast<double>(output.iterations) << '\n';
	for (std::size_t index{}; const int64_t count : output.meso_histogram)
	{
		os << std::setw(5) << index << std::setw(10) << count << '\n';
		++index;
	}
	for (std::size_t index{}; const int64_t count : output.boom_histogram)
	{
		os << std::setw(5) << index << std::setw(10) << count << '\n';
		++index;
	}
	return os;
}


}  // namespace sf