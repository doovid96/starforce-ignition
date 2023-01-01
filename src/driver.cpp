#include "Timer.hpp"
#include "Engine.hpp"

#include <iostream>
#include <cstdint>

enum Equip: int32_t
{
	GOLLUX = 150,
	CRA = 150,
	ABSOLAB = 160,
	ARCANE = 200,
	ETERNAL = 250
};


enum IterationSize : uint64_t
{
	TEST    = 0x1ULL << 10,
	SMALL   = 0x1ULL << 15,
	MEDIUM  = 0x1ULL << 20,
	LARGE   = 0x1ULL << 25,
	EXTREME = 0x1ULL << 30
};


void run()
{
	const int32_t equip{ARCANE};
	const int8_t start_star{0};
	const int8_t goal_star{22};

	const sf::MVPType mvp{sf::MVPType::RED};

	const sf::EventFlags event_flags{sf::EventType::NONE};
	std::cout << event_flags << '\n';

	//const sf::GuardFlags guard_flags{12, 13, 14, 15, 16};
	const sf::GuardFlags guard_flags{sf::Flags::NONE};

	//const sf::CatchFlags catch_flags{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24};
	//const sf::CatchFlags catch_flags{sf::Flags::NONE};
	const sf::CatchFlags catch_flags{17, 18, 19, 20, 21};

	sf::Input input{equip, start_star, goal_star, mvp, event_flags, guard_flags, catch_flags};

	const int32_t concurrency{32};
	sf::Engine engine(concurrency);

	sf::Output output = engine.run(input, LARGE);
	std::cout << output << '\n';

}


int main()
{
	run();
	std::cout << "end of main\n";
}