#pragma once
#ifndef MODE_H_INCLUDED
#define MODE_H_INCLUDED

#include "Transform.h"
#include "Text.h"
#include "Audio.h"
#include "Input.h"
#include <string>

/*Parent class for game modes.*/
class Mode
{
public:
	Mode();
	virtual ~Mode();

	virtual void Update(int delta);
	virtual void Draw();

	/*Confirms to proceed to the next mode.*/
	virtual bool Continue();

protected:
	Audio* _audio;
	Transform::Position _textPosition;
	std::string _textTag;
	int _textSize;
	bool _continue;

	/*Load your audio into memory.*/
	virtual void LoadAudio();
	/*Load your graphics into memory.*/
	virtual void LoadGraphics();

};
#endif