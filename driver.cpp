#include "Timer.hpp"
#include "Starforce.hpp"

#include <iostream>
#include <cstdint>


void run()
{
	const int32_t equip{200};
	const int8_t start_star{0};
	const int8_t goal_star{22};

	const sf::MVPType mvp{sf::MVPType::RED};

	const sf::EventFlags event_flags{sf::EventType::NONE};
	std::cout << event_flags << '\n';

	//const sf::GuardFlags guard_flags{12, 13, 14, 15, 16};
	const sf::GuardFlags guard_flags{sf::Flags::NONE};
	//std::cout << guard_flags << '\n';

	//const sf::CatchFlags catch_flags{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24};
	//const sf::CatchFlags catch_flags{sf::Flags::NONE};
	const sf::CatchFlags catch_flags{20, 21};
	//std::cout << catch_flags << '\n';

	sf::Input input{equip, start_star, goal_star, mvp, event_flags, guard_flags, catch_flags};

	const int32_t concurrency{32};
	sf::Engine engine(concurrency);

	sf::Output results = engine.run(input, 32'000'000ULL);
	std::cout << results << '\n';
}


int main()
{
	Timer timer{"main"};
	run();
}