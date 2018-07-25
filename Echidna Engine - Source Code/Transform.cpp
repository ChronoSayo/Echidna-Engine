#include "Transform.h"

Transform::Transform()
{
}

Transform::~Transform()
{
}

//MOVEMENT BEGIN
void Transform::Move(int x, int y, float delta)
{
	_position.x += int(x * (delta / 1000));
	_position.y += int(y * (delta / 1000));
}

void Transform::Move(Transform::Velocity velocity, float delta)
{
	Move(velocity.x, velocity.y, delta);
}

void Transform::MoveUp(float delta)
{
	_position.y -= int(_velocity.y * (delta / 1000));
}

void Transform::MoveDown(float delta)
{
	_position.y += int(_velocity.y * (delta / 1000));
}

void Transform::MoveLeft(float delta)
{
	_position.x -= int(_velocity.x * (delta / 1000));
}

void Transform::MoveRight(float delta)
{
	_position.x += int(_velocity.x * (delta / 1000));
}
//MOVEMENT END

//SET VALUE BEGIN
void Transform::SetPosition(int x, int y)
{
	_position.x = x;
	_position.y = y;
}

void Transform::SetPosition(Transform::Position position)
{
	_position = position;
}

void Transform::SetVelocity(int x, int y)
{
	_velocity.x = x;
	_velocity.y = y;
}

void Transform::SetVelocity(Transform::Velocity velocity)
{
	_velocity = velocity;
}

void Transform::SetSize(int w, int h)
{
	_size.w = w;
	_size.h = h;
}

void Transform::SetSize(Transform::Size size)
{
	_size = _size;
}

void Transform::SetColor(int r, int g, int b)
{
	_color.r = r;
	_color.g = g;
	_color.b = b;
}

void Transform::SetColor(Transform::Color color)
{
	_color = color;
}
//SET VALUE END

//GET VALUE BEGIN
Transform::Position Transform::GetPosition()
{
	return _position;
}

Transform::Velocity Transform::GetVelocity()
{
	return _velocity;
}

Transform::Size Transform::GetSize()
{
	return _size;
}

Transform::Color Transform::GetColor()
{
	return _color;
}
//GET VALUE END

//MISC BEGIN
void Transform::AddVelocity(int x, int y)
{
	_velocity.x += x;
	_velocity.y += y;
}

void Transform::AddVelocity(Transform::Velocity velocity)
{
	AddVelocity(velocity.x, velocity.y);
}

void Transform::SubVelocity(int x, int y)
{
	_velocity.x -= x;
	_velocity.y -= y;
}

void Transform::SubVelocity(Transform::Velocity velocity)
{
	SubVelocity(velocity.x, velocity.y);
}

void Transform::InvertVelocityX()
{
	_velocity.x *= -1;
}

void Transform::InvertVelocityY()
{
	_velocity.y *= -1;
}

void Transform::SetPositionX(int x)
{
	_position.x = x;
}

void Transform::SetPositionY(int y)
{
	_position.y = y;
}

void Transform::SetVelocityX(int x)
{
	_velocity.x = x;
}

void Transform::SetVelocityY(int y)
{
	_velocity.y = y;
}

void Transform::SetSizeW(int w)
{
	_size.w = w;
}

void Transform::SetSizeH(int h)
{
	_size.h = h;
}
//MISC END