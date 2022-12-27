#include "Starforce.hpp"


namespace sf
{


std::ostream& operator<<(std::ostream& os, const EventFlags& event_flags)
{
	return os << "DISCOUNT " << event_flags.discount << "\nPASS " << event_flags.pass << '\n';
}


EventFlags::EventFlags(std::initializer_list<EventType> event_list)
{
	for (EventType event_type : event_list)
	{
		switch(event_type)
		{
		case EventType::NONE:
			discount = false;
			pass = false;
			break;
		case EventType::DISCOUNT:
			discount = true;
			break;
		case EventType::PASS:
			pass = true;
			break;
		case EventType::SHINING:
			discount = true;
			pass = true;
		}
	}
}


bool EventFlags::get_discount() const
{
	return discount;
}


bool EventFlags::get_pass() const
{
	return pass;
}


std::ostream& operator<<(std::ostream& os, const GuardFlags& guard_flags)
{
	for (std::size_t star{12}; star < 12 + guard_flags.flags.size(); ++star)
	{
		os << star << ' ' << static_cast<int>(guard_flags.flags.test(star + GuardFlags::offset)) << '\n';
	}
	return os;
}


std::ostream& operator<<(std::ostream& os, const CatchFlags& catch_flags)
{
	for (std::size_t star{}; star < catch_flags.flags.size(); ++star)
	{
		os << star << ' ' << static_cast<int>(catch_flags.flags.test(star)) << '\n';
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


Output& Output::operator+=(const Output& other)
{
	iterations += other.iterations;
	mesos += other.mesos;
	booms += other.booms;
	chance_times += other.chance_times;
	return *this;
}


Engine::Engine(const int32_t concurrency)
	: concurrency{concurrency}
{
	if (concurrency < 1 || concurrency > 32)
	{
		throw std::out_of_range("Concurrency is out of range [1,32].");
	}
}


void Engine::validate(const Input& input)
{
	Timer timer{"validate"};
	const int32_t level = input.get_equipment_level();
	if (level < 0 || level > 300)
	{
		throw std::out_of_range("Equipment level is out of range.");
	}
	const int8_t start = input.get_start();
	if (start < 0 || start > 24)
	{
		throw std::out_of_range("Starting starforce level is out of range.");
	}
	const int8_t goal = input.get_goal();
	if (goal < 1 || goal > 25)
	{
		throw std::out_of_range("Goal starforce level is out of range.");
	}
	if (start >= goal)
	{
		throw std::out_of_range("Starting starforce level must be less than goal starforce level.");
	}
	if (goal > star_limit(level))
	{
		throw std::out_of_range("Unable to simulate star force past the star limit.");
	}
}


int8_t Engine::star_limit(const int32_t equipment_level)
{
	int8_t limit;
	if (equipment_level < 0)
	{
		throw std::out_of_range("Unable to calculate star limit for equipment requiring a negative character level.");
	}
	if (equipment_level < 95)
	{
		limit = 5;
	}
	else if (equipment_level < 108)
	{
		limit = 8;
	}
	else if (equipment_level < 118)
	{
		limit = 10;
	}
	else if (equipment_level < 128)
	{
		limit = 15;
	}
	else if (equipment_level < 138)
	{
		limit = 20;
	}
	else if (equipment_level < 301)
	{
		limit = 25;
	}
	else
	{
		throw std::out_of_range("Unable to calculate star limit for equipment requiting a character level above 300.");
	}
	return limit;
}


void Engine::init(const Input& input)
{
	Timer timer{"init"};
	calculate_costs(input);
	calculate_rates(input);
}


void Engine::calculate_costs(const Input& input)
{
	std::vector<int64_t> base_costs = calculate_base_costs(input);
	default_costs = base_costs;

	const double rate = calculate_mvp_discount(input);
	if (rate)
	{
		const int8_t stop = std::min(input.get_goal(), static_cast<int8_t>(16));
		std::transform(default_costs.cbegin(), default_costs.cbegin() + stop, base_costs.cbegin(), default_costs.begin(),
			[rate](const int64_t default_cost, const int64_t base_cost) -> int64_t
			{
				return default_cost - std::floor(rate * base_cost);
			});
	}
	if (input.get_events().get_discount())
	{
		std::transform(default_costs.cbegin(), default_costs.cend(), default_costs.begin(),
			[](const int64_t default_cost)
			{
				return default_cost - std::floor(0.3 * default_cost);
			});
	}
	chance_time_costs = default_costs;
	GuardFlags guard_flags = input.get_guards();
	const int8_t guard_end = std::min(input.get_goal(), static_cast<int8_t>(17));
	for (int8_t star{12}; star < guard_end; ++star)
	{
		if (guard_flags[star])
		{
			default_costs[star] += base_costs[star];
		}
	}
	if (input.get_events().get_pass())
	{
		if (input.get_goal() > 15)
		{
			default_costs[15] = chance_time_costs[15];
		}
	}
}


double Engine::calculate_mvp_discount(const Input& input)
{
	const MVPType mvp = input.get_mvp();
	double discount_rate;
	switch (mvp)
	{
	case MVPType::NONE:
		discount_rate = 0.0;
		break;
	case MVPType::BRONZE:
		discount_rate = 0.0;
		break;
	case MVPType::SILVER:
		discount_rate = 0.03;
		break;
	case MVPType::GOLD:
		discount_rate = 0.05;
		break;
	case MVPType::DIAMOND:
		discount_rate = 0.10;
		break;
	case MVPType::RED:
		discount_rate = 0.10;
		break;
	default:
		discount_rate = 0.00;
	}
	return discount_rate;
}


std::vector<int64_t> Engine::calculate_base_costs(const Input& input)
{
	const int8_t goal = input.get_goal();
	const int32_t level = input.get_equipment_level();
	std::vector<int64_t> base_costs(input.get_goal());
	const auto formula = [](const int8_t star, const int32_t level, const double exponent, const int32_t divisor) -> int64_t
	{
		return 100ULL * std::llround(std::pow(level, 3.0) * std::pow(star + 1, exponent) / divisor + 10);
	};
	for (int8_t star{}; star < goal; ++star)
	{
		base_costs[star] = formula(star, level, 1.0, 2'500);
	}
	for (int8_t star{10}; star < goal; ++star)
	{
		base_costs[star] = formula(star, level, 2.7, 40'000);
	}
	for (int8_t star{15}; star < goal; ++star)
	{
		base_costs[star] = formula(star, level, 2.7, 20'000);
	}
	return base_costs;
}


void Engine::calculate_rates(const Input& input)
{
	const int8_t size = input.get_goal();
	up_rates = std::vector<double>(size);
	stay_rates = std::vector<double>(size);
	down_rates = std::vector<double>(size);
	std::copy_n(UP_RATES.cbegin(), size, up_rates.begin());
	std::copy_n(STAY_RATES.cbegin(), size, stay_rates.begin());
	std::copy_n(DOWN_RATES.cbegin(), size, down_rates.begin());

	CatchFlags catch_flags = input.get_catches();
	for (int8_t star{}; star < size; ++star)
	{
		if (catch_flags[star])
		{
			const double previous_up{up_rates[star]};
			up_rates[star] *= 1.045;
			stay_rates[star] = (stay_rates[star] / (1.0 - previous_up)) * (1.0 - up_rates[star]);
			down_rates[star] = (down_rates[star] / (1.0 - previous_up)) * (1.0 - up_rates[star]);
		}
	}
	std::transform(stay_rates.cbegin(), stay_rates.cend(), up_rates.cbegin(), stay_rates.begin(), std::plus<double>());
	std::transform(down_rates.cbegin(), down_rates.cend(), stay_rates.cbegin(), down_rates.begin(), std::plus<double>());
	const int8_t guard_end = std::min(size, static_cast<int8_t>(17));
	GuardFlags guard_flags = input.get_guards();
	for (int8_t star{12}; star < guard_end; ++star)
	{
		if (guard_flags[star])
		{
			down_rates[star] = 1.0;
		}
	}
	if (input.get_events().get_pass())
	{
		if (size > 5)
		{
			up_rates[5] = 1.0;
		}
		if (size > 10)
		{
			up_rates[10] = 1.0;
		}
		if (size > 15)
		{
			up_rates[15] = 1.0;
		}
	}
}


std::ostream& operator<<(std::ostream& os, const Engine& engine)
{
	os << "Threads: " << engine.concurrency << '\n';
	std::array<int, 6> widths = {6, 12, 12, 10, 10, 10};
	std::array<std::string_view, 6> headers = {"STAR", "DEFAULT", "CHANCE", "UP", "STAY", "DOWN"};
	for (int i{}; const std::string_view header : headers)
	{
		
		os << std::setw(widths[i]) << header;
		++i;
	}
	os << '\n';
	for (std::size_t i{}; i < engine.default_costs.size(); ++i)
	{
		os  << std::setw(widths[0]) << i
			<< std::setw(widths[1]) << engine.default_costs[i]
			<< std::setw(widths[2]) << engine.chance_time_costs[i]
			<< std::setw(widths[3]) << engine.up_rates[i]
			<< std::setw(widths[4]) << engine.stay_rates[i]
			<< std::setw(widths[5]) << engine.down_rates[i] << '\n';
	}
	return os;
}


Output Engine::run(const Input& input, const int64_t iterations)
{
	validate(input);
	init(input);
	std::cout << *this << '\n';
	std::vector<std::pair<std::thread, Output>> workers(concurrency);

	for (auto& [thread, output] : workers)
	{
		thread = std::thread(
			Engine::iterate,
			std::ref(output),
			input,
			iterations / concurrency,
			default_costs,
			chance_time_costs,
			up_rates,
			stay_rates,
			down_rates);
	}
	for (auto& [thread, output] : workers)
	{
		thread.join();
	}
	Output result;
	for (const auto& [thread, output] : workers)
	{
		result += output;
	}
	return result;
}


void Engine::iterate(
	Output& result,
	const Input input,
	const int64_t iterations,
	std::vector<int64_t> default_costs,
	std::vector<int64_t> chance_time_costs,
	std::vector<double> up,
	std::vector<double> stay,
	std::vector<double> down)
{
	std::default_random_engine engine{std::random_device{}()};
	std::uniform_real_distribution<double> real_distribution{0.0, 1.0};
	Output output{iterations, 0ULL, 0ULL, 0ULL};
	for (int64_t i{}; i < iterations; ++i)
	{
		int8_t star{input.get_start()};
		bool down_flag{false};
		while (star < input.get_goal())
		{
			output.mesos += default_costs[star];
			const double random = real_distribution(engine);
			if (random <= up[star])
			{
				++star;
				down_flag = false;
			}
			else if (random <= stay[star])
			{
				down_flag = false;
			}
			else if (random <= down[star])
			{
				if (down_flag)
				{
					output.mesos += chance_time_costs[star-1];
					++output.chance_times;
					down_flag = false;
				}
				else
				{
					--star;
					down_flag = true;
				}
			}
			else
			{
				star = 12;
				down_flag = false;
				++output.booms;
			}
		}
	}
	result = output;
}


std::ostream& operator<<(std::ostream& os, const Output& output)
{
	os << "Iterations: " << output.iterations << '\n';
	os << "Mesos: " << std::fixed << output.mesos / static_cast<double>(output.iterations) << '\n';
	os << "Booms: " << std::fixed << output.booms / static_cast<double>(output.iterations) << '\n';
	os << "Chance Times: " << std::fixed << output.chance_times / static_cast<double>(output.iterations) << '\n';
	return os;
}


}  // namespace sf
