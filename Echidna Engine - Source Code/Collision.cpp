#include "Collision.h"

Collision* Collision::s_xCol = NULL;

Collision::Collision()
{
}


Collision::~Collision()
{
}

Collision* Collision::GetInstance()
{
	if(s_xCol == NULL)
	{
		s_xCol = new Collision();
	}

	return s_xCol;
}

bool Collision::Collide(GameObject* object1, GameObject* object2)
{
	int topA, bottomA, leftA, rightA, topB, bottomB, leftB, rightB;
	Transform::Position v1 = object1->GetPosition();
	Transform::Size s1 = object1->GetSize();
	Transform::Position v2 = object2->GetPosition();
	Transform::Size s2 = object2->GetSize();

	topA = v1.y;
	bottomA = s1.h + v1.y;
	leftA = v1.x;
	rightA = s1.w + v1.x;

	topB = v2.y;
	bottomB = s2.h + v2.y;
	leftB = v2.x;
	rightB = s2.w + v2.x;

	if (bottomA <= topB || topA >= bottomB || rightA <= leftB || leftA >= rightB)
	{
		//No collision detected
		return false;
	}

	return true;
}