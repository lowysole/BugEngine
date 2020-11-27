#include "USTime.h"
#include "SDL.h"

void USTimer::Start() {
	if (!activated) {
		activated = true;
		frequency = (double) SDL_GetPerformanceFrequency() / 1000000;
		Uint64 counter = SDL_GetPerformanceCounter();
		microseconds = counter / frequency;
	}
}

Uint32 USTimer::Read() {

	if (activated) {
		Uint64 counter = SDL_GetPerformanceCounter();
		return (SDL_GetPerformanceCounter() / frequency);
	}
	else
		return microseconds;
}

Uint32 USTimer::Stop() {
	activated = false;
	microseconds = (SDL_GetPerformanceCounter() / frequency);
	return microseconds;
}

