#include "Output.hpp"

namespace sf
{


Output& Output::operator+=(const Output& other)
{
	iterations += other.iterations;
	mesos += other.mesos;
	booms += other.booms;
	chance_times += other.chance_times;
	return *this;
}


std::ostream& operator<<(std::ostream& os, const Output& output)
{
	os << "Iterations," << output.iterations << '\n';
	os << "Mesos," << std::fixed << output.mesos / static_cast<double>(output.iterations) << '\n';
	os << "Booms," << std::fixed << output.booms / static_cast<double>(output.iterations) << '\n';
	os << "Chance Times," << std::fixed << output.chance_times / static_cast<double>(output.iterations) << '\n';
	os << '\n';
	return os;
}


}  // namespace sf