#pragma once
#ifndef AI_H_INCLUDED
#define AI_H_INCLUDED

#include "GameObject.h"

/*Use this class to add AI behaviors to your GameObject.*/
class AI
{
public:
	/*Add the GameObject which requires AI behaviors.*/
	AI(GameObject* instigator);
	~AI();

	void Update(int delta);

	/*Randomizes the time when it should switch to a new speed. Counts in milliseconds.*/
	void RandomMovement(int minNewMoveTime, int maxNewMoveTime);
	/*Instigator chases the GameObject set in the parameter.*/
	void ChaseGameObject(GameObject* target);
	/*Instigator mirrors the GameObject set in the parameter.*/
	void MirrorMovement(GameObject* target);

private:
	enum Behavior
	{
		None, //Fail safe.
		RandomMove,
		Chase,
		Mirror
	};

	GameObject* _instigator, *_target;
	Behavior _behavior;
	Timer _timer;
	//For RandomMovement.
	int _newMoveTick, _newMoveTime;
	Transform::Velocity _randomVelocity;
	//For Mirror.
	Transform::Position _oldTargetPosition;

	/*Runs the active AI behavior in Update().*/
	void StateHandler(float delta);
	/*Randomizer for true or false situations.*/
	bool GetFiftyFifty();

	void SetRandomMovement();
	void RandomMovementTimer(float delta);
	void AdjustChaseMovement(float delta);
	void MirrorPrey(float delta);
};

#endif