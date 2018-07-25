#pragma once
#ifndef COLLISION_H_INCLUDED
#define COLLISION_H_INCLUDED

#include "GameObject.h"

/*Handles collision detection.*/
class Collision
{
public:
	static Collision* GetInstance();

	Collision();
	~Collision();

	/*Box collision. Checks if two objects overlap.*/
	bool Collide(GameObject* object1, GameObject* object2);

private:
	static Collision* s_xCol;
};

#endif