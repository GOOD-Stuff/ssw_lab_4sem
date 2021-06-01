#ifndef CLASS_TIMER_INCLUDED_H
#define CLASS_TIMER_INCLUDED_H

#include <chrono>

class timer
{
private:
	std::chrono::steady_clock::time_point begin;

public:
	timer() { reset(); }

	void reset()
	{
		begin = std::chrono::steady_clock::now();
	}
	
	long long get_elapsed_time() const
	{
		return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - begin).count();

	}
};

#endif