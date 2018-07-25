#pragma once
#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "GameObject.h"
#include "Input.h"

/*Example of Player controlled GameObject.*/
class Player : public virtual GameObject
{
public:
	Player(Position position, Velocity velocity);
	~Player();

	void Update(int delta);
	void Draw();

	void AddClips(SDL_Rect* sprite, int columns, int rows);

private:
	/*Player's animation state. To keep track of which way the player is facing*/
	enum AnimationState
	{
		Neutral,
		Up,
		Right,
		Down,
		Left
	};

	/*Make a player sprite with the amount of frames it should include. This variable will be assigned to GameObject's 
	_sprite in AddClips().*/
	SDL_Rect _playerSprite[6];

	void PlayerInput(float delta);
	void ScreenLimit();
};

#endif