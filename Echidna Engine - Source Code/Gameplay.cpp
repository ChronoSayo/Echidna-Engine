#include "Gameplay.h"

Gameplay::Gameplay() : Mode()
{
	Transform::Size size = Render::GetInstance()->GetSize();

	//0: Player. 0 >: Enemies.
	int speed = 250;
	//Create Player and starts in the middle of the screen.
	_gameObjects.push_back(new Player(Transform::Position(size.w / 2, size.h / 2), Transform::Velocity(speed, speed)));
	//Create Enemy and starts in lower right corner. Has half the speed.
	_gameObjects.push_back(new Enemy(Transform::Position(size.w - 200, size.h - 100), Transform::Velocity(speed / 2, speed / 2)));
	//Create Enemy and starts in upper left corner.
	_gameObjects.push_back(new Enemy(Transform::Position(100, 100), Transform::Velocity(speed, speed)));
	//Create Enemy and starts in lower left corner. Has double the speed.
	_gameObjects.push_back(new Enemy(Transform::Position(100, size.h - 100), Transform::Velocity(speed * 2, speed * 2)));

	//Element 1 chases the player. Element 2 has random movements. Element 3 mirrors player's movement.
	dynamic_cast<Enemy*>(_gameObjects[1])->SetAIChasePlayer(_gameObjects[0]);
	dynamic_cast<Enemy*>(_gameObjects[2])->SetAIRandomMovement(1000, 5000);
	dynamic_cast<Enemy*>(_gameObjects[3])->SetAIMirrorPlayer(_gameObjects[0]);

	//Title placements.
	Text::GetInstance()->ChangePositionY(10, _textTag);
	Text::GetInstance()->ChangeColor(Transform::Color().Blue(), _textTag);
	Text::GetInstance()->Create("Use arrow keys to move", "instructions", 
		_textPosition.x, 65, 30, Transform::Color().White());
}

Gameplay::~Gameplay()
{
	if (_gameObjects.size() > 0)
	{
		for (unsigned int i = 0; i < _gameObjects.size(); i++)
		{
			delete _gameObjects[i];
		}
		_gameObjects.clear();
	}
}

void Gameplay::LoadAudio()
{
	Mode::LoadAudio();

	/*TODO: Call Audio and add audio into its list.*/

	//_audio = Audio::GetInstance();
	//_audio->AddSoundFX("audio.wav", "Audio");
}

void Gameplay::LoadGraphics()
{
	Mode::LoadGraphics();

	/*TODO: Call Render and add graphics into its list.*/

	//Render* _render = Render::GetInstance();
	//render->AddSurface(_render->LoadImage("game background.png"), "background.png", Transform::Position().Zero(), false);
}

void Gameplay::Update(int delta)
{
	Mode::Update(delta);

	for(unsigned int i = 0; i < _gameObjects.size(); i++)
		_gameObjects[i]->Update(delta);

	//Collision update. If any enemy collide with player, next mode will be initiated.
	for (unsigned int i = 1; i < _gameObjects.size(); i++)
	{
		if (Collision::GetInstance()->Collide(_gameObjects[0], _gameObjects[i]))
			_continue = true;
	}
}

void Gameplay::Draw()
{
	for (unsigned int i = 0; i < _gameObjects.size(); i++)
		_gameObjects[i]->Draw();

	//TODO: Uncomment when applied background.
	//Render::GetInstance()->ApplySurface(_background, Transform::Position().Zero());

	Text::GetInstance()->Draw();
}

bool Gameplay::Continue()
{
	return Mode::Continue();
}