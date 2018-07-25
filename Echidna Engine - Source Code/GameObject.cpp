#include "GameObject.h"

GameObject::GameObject() : Transform()
{
	_surface = NULL;
	_sprite = NULL;

	//Example of what a filename could be.
	_filename = "FilePath\\filname.png";

	_activeFrame = 0;

	_timer.Start();
}

GameObject::~GameObject()
{
	SDL_FreeSurface(_surface);
}

void GameObject::Update(int delta)
{
}

void GameObject::Draw()
{
	Render::GetInstance()->ApplySurface(_surface, GetPosition(), &_sprite[_activeFrame]);
}

void GameObject::Animate(int endFrame)
{
	_frameTick += _timer.GetTicks();
	if (_frameTick >= _frameTime)
	{
		_activeFrame = (_activeFrame + 1) % endFrame;
		_frameTick = 0;
	}
	//Restarts timer for GetTicks().
	_timer.Start();
}

void GameObject::SetFrame(int frame)
{
	_activeFrame = frame;
}

void GameObject::ScreenLimit()
{
	Size s = Render::GetInstance()->GetScreenResolutions();
	
	//Up limit
	if(GetPosition().y < 0) 
		SetPositionY(0);
	//Down limit
	if(GetPosition().y + GetSize().h > s.h) 
		SetPositionY(s.h - GetSize().h);
	//Left limit
	if(GetPosition().x < 0) 
		SetPositionX(0);
	//Right limit
	if(GetPosition().x + GetSize().w > s.w)
		SetPositionX(s.w - GetSize().w);
}

void GameObject::AddClips(SDL_Rect* sprite, int columns, int rows)
{
	int w = GetSize().w;
	int h = GetSize().h;
	int frame = 0;

	for (int i = 0; i < columns; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			sprite[frame].x = w * j;
			sprite[frame].y = h * i;
			sprite[frame].w = w;
			sprite[frame].h = h;
			frame++;
		}
	}

	_sprite = sprite;
}