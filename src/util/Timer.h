#pragma once

#include <chrono>
#include <thread>

class Timer final
{
	// compile time constants
private:
	static constexpr double NANO{ 1.0 / 1'000'000'000 };
	static constexpr bool PRINT_DEBUG_TEXT{ false };

private:
	std::chrono::steady_clock clock;
	std::chrono::time_point<std::chrono::steady_clock> lastFrameStart{ clock.now() };

	double dt{};
	double totalSecondsElapsed{};	// seconds

private:
	void preciseSleep(double seconds);

public:
	void wait(const unsigned int targetFPS);

	// returns time since last wait call in seconds
	double getDeltaTime()			{ return this->dt;						}
	double getTotalTimeElapsed()	{ return this->totalSecondsElapsed;		}
};