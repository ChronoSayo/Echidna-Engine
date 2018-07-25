#pragma once
#ifndef ENDING_H_INCLUDED
#define ENDING_H_INCLUDED

#include "Mode.h"

class Ending : public virtual Mode
{
public:
	Ending();
	~Ending();

	void Update(int delta);
	void Draw();

	bool Continue();

private:	
	/*Load your audio into memory.*/
	void LoadAudio();
	/*Load your graphics into memory.*/
	void LoadGraphics();
};

#endif