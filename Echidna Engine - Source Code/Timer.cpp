#include "Timer.h"

Timer::Timer()
{
	_tick = 0;
	_pauseTick = 0;
	_paused = false;
	_started = false;
}


Timer::~Timer()
{
}

void Timer::Start()
{
	_started = true;
	_paused = false;
	_tick = (int)SDL_GetTicks();
}

void Timer::Stop()
{
	_started = false;
	_paused = false;
}

void Timer::Pause()
{
	if(_started && !_paused)
	{
		_paused = true;
		_pauseTick = SDL_GetTicks() - _tick;
	}
}

void Timer::Unpause()
{
	if(_paused)
	{
		_paused = false;
		_tick = SDL_GetTicks() - _pauseTick;
		_pauseTick = 0;
	}
}

int Timer::GetTicks()
{
	if(_started)
	{
		if(_paused)
		{
			return _pauseTick;
		}
		else
		{
			return int(SDL_GetTicks()) - _tick;
		}
	}

	return 0;
}

bool Timer::IsStarted()
{
	return _started;
}

bool Timer::IsPaused()
{
	return _paused;
}