#pragma once
#ifndef GAMEOBJECT_H_INCLUDED
#define GAMEOBJECT_H_INCLUDED

#include "Render.h"
#include "Timer.h"
#include <string>

/*Inherit this class when creating an object inside the application. */
class GameObject : public Transform
{
public:
	GameObject();
	~GameObject();

	virtual void Update(int delta);
	virtual void Draw();

	/*Stops object from leaving the screen. Run in Update(). Do not run this if you want a GameObject appearing outside of the screen.*/
	virtual void ScreenLimit();

protected:
	Timer _timer;
	SDL_Surface* _surface;
	SDL_Rect* _sprite;
	std::string _filename;
	/*The speed of the animation cycling. Counts in milliseconds.*/
	float _frameTime;

	/*Cycles through spritesheet to show appropriate frame. Returns to starting frame when passing endFrame.*/
	virtual void Animate(int endFrame);
	/*Sets _activeFrame into specified frame.*/
	virtual void SetFrame(int frame);
	/*Loops through sprite sheet, based on size, to find all the frames and then divides them.*/
	virtual void AddClips(SDL_Rect* sprite, int columns, int rows);

private:
	/*The frame to draw, from the sprite sheet. */
	int _activeFrame;
	/*The timer running until the next frame in the sprite sheet.*/
	float _frameTick;
};

#endif