#include "Enemy.h"

Enemy::Enemy(Position position, Velocity velocity) : GameObject()
{
	Transform::SetPosition(position);
	Transform::SetVelocity(velocity);

	_filename = "Graphics//enemy-sheet.png";
	_surface = Render::GetInstance()->LoadImage(_filename);
	int columns = 2;
	int rows = 3;
	_lastFrame = columns * rows;

	//TODO: Add fail safe if file wasn't loaded.
	if (Render::GetInstance()->IsLoaded())
	{
		SetSize(_surface->w / rows, _surface->h / columns);
		Render::GetInstance()->AddSurface(_surface, _filename, GetPosition(), false);
	}

	_frameTime = 250;//0.25 seconds.

	AddClips(_enemySprite, columns, rows);

	_ai = new AI(this);
}

Enemy::~Enemy()
{
	if (_ai != NULL)
	{
		delete _ai;
		_ai = NULL;
	}
}

void Enemy::Update(int delta)
{
	GameObject::Update(delta);

	_ai->Update(delta);

	ScreenLimit();
	Animate(_lastFrame);
}

void Enemy::ScreenLimit()
{
	GameObject::ScreenLimit();
}

void Enemy::Draw()
{
	GameObject::Draw();
}

void Enemy::AddClips(SDL_Rect* sprite, int columns, int rows)
{
	GameObject::AddClips(sprite, columns, rows);
}

void Enemy::SetAIRandomMovement(int minNewMoveTime, int maxNewMoveTime)
{
	_ai->RandomMovement(minNewMoveTime, maxNewMoveTime);
}

void Enemy::SetAIChasePlayer(GameObject* player)
{
	_ai->ChaseGameObject(player);
}

void Enemy::SetAIMirrorPlayer(GameObject * player)
{
	_ai->MirrorMovement(player);
}
