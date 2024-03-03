#include"time.h"
#include"commonfunc.h"
Time::Time() {
	start_ticks = 0;
	pause_ticks = 0;
	is_start = false;
	is_pause = false;


}
Time::~Time() {

}
void Time::start() {
	is_start = true;
	is_pause = false;
	start_ticks = SDL_GetTicks();


}

void Time::stop() {
	is_start = false;
	is_pause = false;

}

void Time::pause() {
	if (is_start == true && is_pause == false) {
		is_pause = true;
		pause_ticks = SDL_GetTicks() - start_ticks;
	}
	

}

void Time::unpause() {
	if (is_pause == true) {
		is_pause = false;
		start_ticks = SDL_GetTicks() - pause_ticks;
		pause_ticks = 0;
	}

}

int Time::getTicks() {
	if (is_start == true)
	{
		if (is_pause == true) {
			return pause_ticks;
		}
		else {
			return SDL_GetTicks() - start_ticks;
		}
	}
	return 0;
}
bool Time::is_started() {
	return is_start;
}
bool Time::is_paused() {

	return is_pause;
}