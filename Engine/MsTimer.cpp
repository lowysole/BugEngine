#include "MSTimer.h"
#include "SDL.h"

void MSTimer::Start() {
	if (!activated) {
		activated = true;
		time = SDL_GetTicks();
	}
}

Uint32 MSTimer::Read() {

	if (activated)
		return (SDL_GetTicks() - time);
	else
		return time;
}

Uint32 MSTimer::Stop() {
	activated = false;
	time = (SDL_GetTicks() - time);
	return time;
}