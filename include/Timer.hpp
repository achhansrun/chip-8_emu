
#ifndef TIMER_HPP
#define TIMER_HPP

#include <cstdint>


class Timer
{
protected:
	uint8_t counter;
public:
	Timer() {};
	Timer(uint8_t initial_value) :
		counter(initial_value) {};
	void set_timer(uint8_t value);
	uint8_t get_counter_value();
	void update_timer();
};

class SoundTimer: Timer
{
protected:
	uint8_t counter;
public:
	SoundTimer() {};
	SoundTimer(uint8_t initial_value);
	~SoundTimer();
	void update_timer();
};

#endif