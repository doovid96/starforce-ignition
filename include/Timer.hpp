#ifndef TIMER_HPP
#define TIMER_HPP

#include <iostream>
#include <chrono>


class Timer
{

public:

	explicit Timer();
	explicit Timer(const std::string description);
	~Timer();

private:

	std::string description;
	std::chrono::time_point<std::chrono::steady_clock> start;

};

#endif