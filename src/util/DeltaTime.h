#pragma once

#include <chrono>
#include <thread>

class DeltaTime final
{
private:
	std::chrono::steady_clock clock;
	std::chrono::time_point<std::chrono::steady_clock> lastFrameStart{ clock.now() };

	float dt{};
	float totalSecondsElapsed{};	// seconds
	long long totalNanosecondsElapsed{};

private:
	void preciseSleep(double seconds);

public:
	void wait();	// waits 1/60th of a second and updates internal vars	// TODO take target fps as input

	float getDT()							{ return this->dt;						}
	float getTotalTimeElapsed()				{ return this->totalSecondsElapsed;		}
	long long getTotalNanosecondsElapsed()	{ return this->totalNanosecondsElapsed; }
};