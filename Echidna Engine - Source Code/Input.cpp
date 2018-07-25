#include "Input.h"

Input* Input::_staticInput = NULL;

Input::Input()
{
	_returnPressed = false;
	_escapePressed = false;

	_pressedKeys.insert(std::make_pair(SDLK_RETURN, false));
	_pressedKeys.insert(std::make_pair(SDLK_ESCAPE, false));

	_pressedKeys.insert(std::make_pair(SDLK_UP, false));
	_pressedKeys.insert(std::make_pair(SDLK_DOWN, false));
	_pressedKeys.insert(std::make_pair(SDLK_LEFT, false));
	_pressedKeys.insert(std::make_pair(SDLK_RIGHT, false));
}

Input::~Input()
{
}

Input* Input::GetInstance()
{
	if (_staticInput == NULL)
	{
		_staticInput = new Input();
	}

	return _staticInput;
}

void Input::GetSDLInput(SDL_Event event)
{
	_event = event;
	RegisterKeyPress();
}

bool Input::GetKeyReturn()
{
	return OnePress(_returnPressed, SDLK_RETURN);
}

bool Input::GetKeyEscape()
{
	return OnePress(_escapePressed, SDLK_ESCAPE);
}

bool Input::GetKeyArrowUp()
{
	return _pressedKeys[SDLK_UP];
}

bool Input::GetKeyArrowDown()
{
	return _pressedKeys[SDLK_DOWN];
}

bool Input::GetKeyArrowLeft()
{
	return _pressedKeys[SDLK_LEFT];
}

bool Input::GetKeyArrowRight()
{
	return _pressedKeys[SDLK_RIGHT];
}

void Input::RegisterKeyPress()
{
	if (_event.type == SDL_KEYDOWN)
	{
		EnableKey(_event.key.keysym.sym, true);
	}
	if (_event.type == SDL_KEYUP)
	{
		EnableKey(_event.key.keysym.sym, false);
	}
}

void Input::EnableKey(SDL_Keycode key, bool enable)
{
	if (_pressedKeys.find(key) != _pressedKeys.end())
		_pressedKeys[key] = enable;
}

bool Input::OnePress(bool& currentPressed, SDL_Keycode key)
{
	bool pressed = false;

	if (_pressedKeys[key] && !currentPressed)
	{
		currentPressed = true;
		pressed = true;
	}
	else if (!_pressedKeys[key] && currentPressed)
		currentPressed = false;

	return pressed;
}
