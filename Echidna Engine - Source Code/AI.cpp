#include "AI.h"

AI::AI(GameObject* instigator)
{
	_instigator = instigator;

	_timer.Start();
}

AI::~AI()
{
}

void AI::Update(int delta)
{
	StateHandler((float)delta);
}

void AI::RandomMovement(int minNewMoveTime, int maxNewMoveTime)
{
	_newMoveTime = rand() % maxNewMoveTime + minNewMoveTime;
	_behavior = RandomMove;
	SetRandomMovement();
}

void AI::ChaseGameObject(GameObject* target)
{
	_target = target;
	_behavior = Chase;
}

void AI::MirrorMovement(GameObject * target)
{
	_target = target;
	_oldTargetPosition = _target->GetPosition();
	_behavior = Mirror;
}

void AI::SetRandomMovement()
{
	Transform::Velocity vel = _instigator->GetVelocity();
	//50% if x = 0, else 50% if velocity = left or right.
	_randomVelocity.x = GetFiftyFifty() ? 0 : GetFiftyFifty() ? -vel.x : vel.x;
	//If x = 0, 50% if velocity = up or down.
	_randomVelocity.y = _randomVelocity.x == 0 ? (GetFiftyFifty() ? -vel.y : vel.y) : 0;
}

void AI::RandomMovementTimer(float delta)
{
	//Time until next randomized movement.
	_newMoveTick += _timer.GetTicks();
	if (_newMoveTick < _newMoveTime)
	{
		_instigator->Move(_randomVelocity, delta);
	}
	else
	{
		_newMoveTick = 0;
		SetRandomMovement();
	}
	//Restarts the tick for GetTick().
	_timer.Start();
}

void AI::AdjustChaseMovement(float delta)
{
	int preyX = _target->GetPosition().x;
	int preyY = _target->GetPosition().y;
	int controlX = _instigator->GetPosition().x;
	int controlY = _instigator->GetPosition().y;

	//Checks if prey is closer horizontally or vertically. Runs appropriate movement based on the values.
	if (abs(preyX - controlX) > abs(preyY - controlY))
	{
		if (preyX > controlX)
			_instigator->MoveRight(delta);
		else if (preyX < controlX)
			_instigator->MoveLeft(delta);
	}
	else
	{
		if (preyY > controlY)
			_instigator->MoveDown(delta);
		else if (preyY < controlY)
			_instigator->MoveUp(delta);
	}
}

void AI::MirrorPrey(float delta)
{
	int preyX = _target->GetPosition().x;
	int preyY = _target->GetPosition().y;
	int oldTargetX = _oldTargetPosition.x;
	int oldTargetY = _oldTargetPosition.y;

	//Compares target's old positions with new. Moves instigator based on that value.
	if (oldTargetX > preyX)
	{
		_instigator->MoveLeft(delta);
		_oldTargetPosition.x = preyX;
	}
	else if (oldTargetX < preyX)
	{
		_instigator->MoveRight(delta);
		_oldTargetPosition.x = preyX;
	}
	else if (oldTargetY < preyY)
	{
		_instigator->MoveDown(delta);
		_oldTargetPosition.y = preyY;
	}
	else if (oldTargetY > preyY)
	{
		_instigator->MoveUp(delta);
		_oldTargetPosition.y = preyY;
	}
}

void AI::StateHandler(float delta)
{
	switch (_behavior)
	{
	case AI::None:
		break;
	case AI::RandomMove:
		RandomMovementTimer(delta);
		break;
	case Chase:
		AdjustChaseMovement(delta);
		break;
	case Mirror:
		MirrorPrey(delta);
		break;
	}
}

bool AI::GetFiftyFifty()
{
	return rand() % 2 == 0;
}
