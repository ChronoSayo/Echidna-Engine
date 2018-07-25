#include "GameMode.h"

GameMode::GameMode()
{
	_memoryCard = new MemoryCard("MemoryCard", "memorycard");
	if(!_memoryCard->FileFound())
	{
		std::vector<std::string> lines{ "Test1", "Test2", "Test3" };
		_memoryCard->CreateFile(lines);
	}
	else
		_memoryCard->Load();

	_modeState = MenuState;
	_currentMode = new StartMenu();

	//Debug stuff.
	_debugTag = "Debug";
	_debug = true;
	/*Use this to mute your game during development.*/
	_enableAudio = true;

	_quit = false;
	_buttonPressed = false;
	
	if(_debug)
		DebugTextInit();
}

GameMode::~GameMode()
{
	if (_memoryCard != NULL)
	{
		delete _memoryCard;
		_memoryCard = NULL;
	}

	if(_currentMode != NULL)
	{
		delete _currentMode;
		_currentMode = NULL;
	}
}

void GameMode::Update(int delta)
{
	_currentMode->Update(delta);
	//Continues into next mode if method returns true.
	if (_currentMode->Continue())
		InitiateNewMode(static_cast<ModeState>(_modeState = ModeState((_modeState + 1) % MAX)));

	Return();

	//Displays mouse position for debug purposes.
	if (_debug)
		DebugTextUpdate();
}

void GameMode::Return()
{
	Input* input = Input::GetInstance();

	if (input->GetKeyEscape())
	{
		if (_modeState == MenuState)
			_quit = true;
		else
			InitiateNewMode(MenuState);
	}
}

void GameMode::InitiateNewMode(ModeState newMode)
{
	Clean();

	_modeState = newMode;

	switch (_modeState)
	{
	case MenuState:
		_currentMode = new StartMenu();
		break;
	case GameplayState:
		_currentMode = new Gameplay();
		break;
	case EndingState:
		_currentMode = new Ending();
		break;
	}

	if (_debug)
		DebugTextInit();
}

void GameMode::Clean()
{
	Text::GetInstance()->RemoveAll();

	Render::GetInstance()->CleanUp();

	//Uncomment when adding audio.
	//if(_enableAudio)
	//	_audio->CleanAll();

	if (_currentMode != NULL)
	{
		_currentMode = NULL;
	}
}

void GameMode::Draw()
{
	_currentMode->Draw();
}

bool GameMode::Quit()
{
	return _quit;
}

void GameMode::DebugTextUpdate()
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	Text::GetInstance()->ChangeText("x: " + std::to_string((long long)x) + " y: " + std::to_string((long long)y), _debugTag);
}

void GameMode::DebugTextInit()
{
	Text::GetInstance()->Create("0, 0", _debugTag, 0, 0, 20, Transform::Color().White());
}