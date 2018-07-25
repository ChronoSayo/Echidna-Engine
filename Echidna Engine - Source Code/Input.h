#pragma once
#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED

#include "SDL.h"
#include <iostream>
#include <map>

class Input
{
public:
	static Input* GetInstance();

	Input();
	~Input();

	void GetSDLInput(SDL_Event event);

	bool GetKeyReturn();
	bool GetKeyEscape();

	bool GetKeyArrowUp();
	bool GetKeyArrowDown();
	bool GetKeyArrowLeft();
	bool GetKeyArrowRight();

private:
	static Input* _staticInput;

	SDL_Event _event;
	//To register button input only once.
	bool _escapePressed, _returnPressed;
	/*Keeps track of pressed keys.*/
	std::map<SDL_Keycode, bool> _pressedKeys;

	/*Listens to key presses.*/
	void RegisterKeyPress();
	/*Handles key input press.*/
	void EnableKey(SDL_Keycode key, bool enable);
	/*Manages key to deal only one press.*/
	bool OnePress(bool& currentPressed, SDL_Keycode key);
};


#endif