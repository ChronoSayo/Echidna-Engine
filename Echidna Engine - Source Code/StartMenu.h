#pragma once
#ifndef STARTMENU_H_INCLUDED
#define STARTMENU_H_INCLUDED

#include "Mode.h"

class StartMenu : public virtual Mode
{
public:
	StartMenu();
	~StartMenu();

	void Update(int delta);
	void Draw();

	bool Continue();

private:	
	/*Load your audio into memory.*/
	void LoadAudio();
	/*Load your background into memory.*/
	void LoadGraphics();
};

#endif