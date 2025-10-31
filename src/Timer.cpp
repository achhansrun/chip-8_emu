
#include "Timer.hpp"
#include <thread>
#include <SDL3/SDL.h>
#include <iostream>

void Timer::update_timer() {
	for (;;)
	{
		if (this->counter > 0)
		{
			this->counter--;
		}
		// std::cout << "Hello from thread!" << std::endl;
		time_t timer;
		time(&timer);
		// std::cout << timer << std::endl;
		double temp = 1/(float)60;
		// std::cout << temp << std::endl;
		// std::cout << (uint32_t)(temp*1000) << std::endl;
		SDL_Delay((uint32_t)(temp*1000));
	}
}

void Timer::set_timer(uint8_t value) {
	this->counter = value;
}

uint8_t Timer::get_counter_value() {
	return this->counter;
}

void SoundTimer::update_timer() {
	// When the timer is nonzero, play a beep
}


SoundTimer::SoundTimer(uint8_t initial_value) : counter(initial_value) {}

SoundTimer::~SoundTimer()
{}