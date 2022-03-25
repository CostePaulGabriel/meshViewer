#ifndef TIMER_H
#define TIMER_H

#include <cmath>
#include <chrono>	//for time
#include <time.h>	//for date

//https://www.techiedelight.com/measure-elapsed-time-program-chrono-library/
class Timer
{
public:
	enum Units { SEC, MILIS, MICROS, NANOS };
	Timer() = default;
	~Timer() = default;

	void start() //< return the time when a function started
	{ 
		mTimer = std::chrono::high_resolution_clock::now();
	} 

	float elapsed(Units unit)	//< Returns the time elapsed(in seconds) after a specific task ends. Note that 1 second = 10^6 ticks (1e-6).
	{
		switch (unit)
		{
		case SEC:
			return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - mTimer).count() * pow(1,-6); break;
		case MILIS:
			return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - mTimer).count() * pow(1,-9); break;
		case NANOS:
		case MICROS:
			throw("Not implemented");
			break;
		}
	}

	static std::string getDateAndTime()
	{
		// https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/ctime-s-ctime32-s-ctime64-s-wctime-s-wctime32-s-wctime64-s?view=msvc-170
		time_t currentTime = time(0);
		char buff[32];
		ctime_s(buff, sizeof(buff), &currentTime);
		std::string res(buff);
		res.pop_back(); //remove the null terminated char
		return res;
	}

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> mTimer;
};

#endif // TIMER_H