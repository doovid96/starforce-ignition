#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "Input.hpp"
#include "Output.hpp"
#include "Timer.hpp"

#include <iostream>
#include <array>
#include <vector>
#include <cstdint>
#include <random>
#include <thread>


namespace sf
{

class Engine
{

	friend std::ostream& operator<<(std::ostream& os, const Engine& engine);
	static constexpr std::array<double, 25> UP_RATES {{
		0.950, // 0
		0.900, // 1
		0.850, // 2
		0.850, // 3
		0.800, // 4
		0.750, // 5
		0.700, // 6
		0.650, // 7
		0.600, // 8
		0.550, // 9
		0.500, // 10
		0.450, // 11
		0.400, // 12
		0.350, // 13
		0.300, // 14
		0.300, // 15
		0.300, // 16
		0.300, // 17
		0.300, // 18
		0.300, // 19
		0.300, // 20
		0.300, // 21
		0.030, // 22
		0.020, // 23
		0.010  // 24
	}};
	static constexpr std::array<double, 25> STAY_RATES {{
		0.050, // 0
		0.100, // 1
		0.150, // 2
		0.150, // 3
		0.200, // 4
		0.250, // 5
		0.300, // 6
		0.350, // 7
		0.400, // 8
		0.450, // 9
		0.500, // 10
		0.000, // 11
		0.000, // 12
		0.000, // 13
		0.000, // 14
		0.679, // 15
		0.000, // 16
		0.000, // 17
		0.000, // 18
		0.000, // 19
		0.630, // 20
		0.000, // 21
		0.000, // 22
		0.000, // 23
		0.000  // 24
	}};
	static constexpr std::array<double, 25> DOWN_RATES {{
		0.000, // 0
		0.000, // 1
		0.000, // 2
		0.000, // 3
		0.000, // 4
		0.000, // 5
		0.000, // 6
		0.000, // 7
		0.000, // 8
		0.000, // 9
		0.000, // 10
		0.550, // 11
		0.594, // 12
		0.637, // 13
		0.686, // 14
		0.000, // 15
		0.679, // 16
		0.679, // 17
		0.672, // 18
		0.672, // 19
		0.000, // 20
		0.630, // 21
		0.776, // 22
		0.686, // 23
		0.594  // 24
	}};

public:

	explicit Engine(const int32_t concurrency);
	Output run(const Input& input, const int64_t iterations);

private:

	static void iterate(
		Output& result,
		const Input input,
		const int64_t iterations,
		const std::vector<int64_t> default_costs,
		const std::vector<int64_t> chance_time_costs,
		const std::vector<double> up,
		const std::vector<double> stay,
		const std::vector<double> down);
	void validate(const Input& input);
	int8_t star_limit(const int32_t equipment_level);
	void init(const Input& input);
	void calculate_costs(const Input& input);
	std::vector<int64_t> calculate_base_costs(const Input& input);
	double calculate_mvp_discount(const Input& input);
	void calculate_rates(const Input& input);

	int32_t concurrency;
	std::vector<int64_t> default_costs;
	std::vector<int64_t> chance_time_costs;
	std::vector<double> up_rates;
	std::vector<double> stay_rates;
	std::vector<double> down_rates;

};


}  // namespace sf

#endif