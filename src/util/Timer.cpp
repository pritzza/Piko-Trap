#include "Timer.h"

#include <iostream>

// genious fella here: https://blat-blatnik.github.io/computerBear/making-accurate-sleep-function/
void Timer::preciseSleep(double seconds)
{
	using namespace std;
	using namespace std::chrono;

	static double estimate = 5e-3;
	static double mean = 5e-3;
	static double m2 = 0;
	static int64_t count = 1;

	while (seconds > estimate) {
		auto start = high_resolution_clock::now();
		this_thread::sleep_for(milliseconds(1));
		auto end = high_resolution_clock::now();

		double observed = (end - start).count() / 1e9;
		seconds -= observed;

		++count;
		double delta = observed - mean;
		mean += delta / count;
		m2 += delta * (observed - mean);
		double stddev = sqrt(m2 / (count - 1));
		estimate = mean + stddev;
	}

	// spin lock
	auto start = high_resolution_clock::now();
	while ((high_resolution_clock::now() - start).count() / 1e9 < seconds);
}

void Timer::wait(const unsigned int targetFPS)
{
	long long targetFrameDuration{ static_cast<long long>(1.f / targetFPS / NANO) }; // in nanoseconds

	// processing time is how long it takes to execute the program loop once
	const std::chrono::nanoseconds ptDuration{ clock.now() - this->lastFrameStart };
	const long long pt{ ptDuration.count() };

	const std::chrono::nanoseconds sleepTime{ std::chrono::nanoseconds(targetFrameDuration) - ptDuration };

	static constexpr int ESTIMATED_SLEEP_RUNTIME{ 10'000 }; // how long I think a call to preciseSleep takes in NS

	if (sleepTime.count() > 10,000)
		preciseSleep(sleepTime.count() * NANO);

	const std::chrono::nanoseconds dtDuration{ clock.now() - this->lastFrameStart };
	const long long dt{ dtDuration.count() };

	this->dt = dt * NANO;

	// once we're done doing all the timing stuff for this frame,
	// we update when our last frame started to base the timing of pt and dt next frame (lil confusing)
	this->lastFrameStart = clock.now();

	if constexpr (PRINT_DEBUG_TEXT)
		std::cout << "pt: " << pt * NANO << " dt: " << dt * NANO << " deviation:" << dt - targetFrameDuration << '\n';

	this->totalSecondsElapsed += dt * NANO;
}