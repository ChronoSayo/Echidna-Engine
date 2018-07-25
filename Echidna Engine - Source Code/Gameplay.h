#pragma once
#ifndef GAMEPLAY_H_INCLUDED
#define GAMEPLAY_H_INCLUDED

#include "Mode.h"
#include "Player.h"
#include "Enemy.h"
#include "Collision.h"

class Gameplay : public virtual Mode
{
public:
	Gameplay();
	~Gameplay();

	void Update(int delta);
	void Draw();

	bool Continue();

private:
	/*All GameObjects compiled into one vector. 0: Player. >1: Enemies.*/
	std::vector<GameObject*> _gameObjects;

	/*Load your audio into memory.*/
	void LoadAudio();
	/*Load your graphics into memory.*/
	void LoadGraphics();
};

#endif