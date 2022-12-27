#include "Timer.hpp"


Timer::Timer()
	: Timer{"NO DESCRIPTION"}
{}


Timer::Timer(std::string description)
	: description{std::move(description)}
	, start{std::chrono::steady_clock::now()}
{}


Timer::~Timer()
{
	const double count = std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count();
	std::cout << '[' << description << ']' << count << '\n';
}