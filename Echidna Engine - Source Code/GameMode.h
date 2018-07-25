#ifndef GAMEMODE_H_INCLUDED
#define GAMEMODE_H_INCLUDED

#include "Render.h"
#include "Audio.h"
#include "StartMenu.h"
#include "Gameplay.h"
#include "Ending.h"
#include "MemoryCard.h"
#include <sstream>
#include <string>

/*Organizes and runs all game modes. Call this from main loop.*/
class GameMode
{
public:
	GameMode();
	~GameMode();

	/*Order goes: Menu > Gameplay > Ending > Menu. MAX is for fail safe.*/
	enum ModeState
	{
		MenuState = 0,
		GameplayState,
		EndingState,
		MAX
	};

	/*Run game modes' Update() here.*/
	void Update(int delta);
	/*Run game modes' Draw() here.*/
	void Draw();

	bool Quit();

private:
	Audio* _audio;
	MemoryCard* _memoryCard;
	Mode* _currentMode;
	ModeState _modeState;
	bool _quit, _buttonPressed;
	bool _debug, _enableAudio;
	std::string _debugTag;

	/*Press Escape key to return to menu. Turn off application if already in menu.*/
	void Return();

	/*Initiates mode and removes previous game mode.*/
	void InitiateNewMode(ModeState newMode);

	/*Renders version text. Use during development.*/
	void DebugTextInit();
	void DebugTextUpdate();

	/*Clears the screen from graphics and audio.*/
	void Clean();
};

#endif