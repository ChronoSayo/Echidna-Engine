#pragma once
#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include "GameObject.h"
#include "AI.h"

/*Example of enemy class. Inherits from GameObject and calls AI class.*/
class Enemy : public virtual GameObject
{
public:
	Enemy(Position position, Velocity velocity);
	~Enemy();

	void Update(int delta);
	void Draw();

	void AddClips(SDL_Rect* sprite, int columns, int rows);

	//Initiate AI behaviors. Assign one of these to Enemy when created.
	void SetAIRandomMovement(int minNewMoveTime, int maxNewMoveTime);
	void SetAIChasePlayer(GameObject* player);
	void SetAIMirrorPlayer(GameObject* player);

protected:
	void ScreenLimit();

private:
	/*Make an enemy sprite with the amount of frames it should include. This variable will be assigned to GameObject's
	_sprite in AddClips().*/
	SDL_Rect _enemySprite[6];
	AI* _ai;
	/*Gets the last frame of the sprite sheet to loop in Animate().*/
	int _lastFrame;
};

#endif