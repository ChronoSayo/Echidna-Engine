#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

#include "SDL.h"

/*This controls application's timer. Use this class to implement time based features. Counts in milliseconds.*/
class Timer
{
public:
	Timer();
	~Timer();

	void Start();
	void Stop();
	void Pause();
	void Unpause();
	int GetTicks();
	bool IsStarted();
	bool IsPaused();

private:
	int _tick;
	int _pauseTick;
	bool _paused;
	bool _started;
};

#endif