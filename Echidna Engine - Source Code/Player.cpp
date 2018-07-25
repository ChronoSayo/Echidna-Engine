#include "Player.h"

Player::Player(Position position, Velocity velocity) : GameObject()
{
	Transform::SetPosition(position);
	Transform::SetVelocity(velocity);

	_filename = "Graphics//player-sheet.png";
	_surface = Render::GetInstance()->LoadImage(_filename);
	int columns = 2;
	int rows = 3;

	if (Render::GetInstance()->IsLoaded())
	{
		SetSize(_surface->w / rows, _surface->h / columns);
		Render::GetInstance()->AddSurface(_surface, _filename, GetPosition(), false);
	}

	AddClips(_playerSprite, columns, rows);
}

Player::~Player()
{
}

void Player::Update(int delta)
{
	GameObject::Update(delta);

	PlayerInput((float)delta);
	ScreenLimit();
}

void Player::ScreenLimit()
{
	GameObject::ScreenLimit();
}

void Player::PlayerInput(float delta)
{
	Input* input = Input::GetInstance();
	if (input->GetKeyArrowUp())
	{
		MoveUp(delta);
		SetFrame(Up);
	}
	else if (input->GetKeyArrowDown())
	{
		MoveDown(delta);
		SetFrame(Down);
	}
	else if (input->GetKeyArrowRight())
	{
		MoveRight(delta);
		SetFrame(Right);
	}
	else if (input->GetKeyArrowLeft())
	{
		MoveLeft(delta);
		SetFrame(Left);
	}
	else
		SetFrame(Neutral);
}

void Player::Draw()
{
	GameObject::Draw();
}

void Player::AddClips(SDL_Rect* sprite, int columns, int rows)
{
	GameObject::AddClips(sprite, columns, rows);
}
