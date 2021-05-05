#include "Timer.h"

Timer::Timer()
{
	Restart();
}

void Timer::Restart()
{
	start = std::chrono::steady_clock::now();
}

long long Timer::GetElapsed_ms()
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count();
}