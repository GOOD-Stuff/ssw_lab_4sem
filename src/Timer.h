#ifndef CLASS_TIMER_H
#define CLASS_TIMER_H

#include <chrono>

class Timer
{
private:
	std::chrono::steady_clock::time_point start;

public:
	Timer();

	void Restart();
	long long GetElapsed_ms();

	// Noncopyable
	Timer(const Timer& stack) = delete;
	Timer& operator=(const Timer& vector) = delete;
};

#endif