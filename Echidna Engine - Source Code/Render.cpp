#include "Render.h"

Render* Render::_staticRender = NULL;

Render::Render() : Transform()
{
	_screen = NULL;

	_isLoaded = true;

	_backgroundColor = Color(0, 0, 0);
}

Render::~Render()
{
	SDL_FreeSurface(_screen);
}

Render* Render::GetInstance()
{
	if(_staticRender == NULL)
	{
		_staticRender = new Render();
	}

	return _staticRender;
}

void Render::AddSurface(SDL_Surface* surface, std::string filename, Position position, bool hide, int alpha)
{
	GameObjectData tempGameObjectData;
	tempGameObjectData.image = surface;
	tempGameObjectData.filename = filename;
	tempGameObjectData.position = position;
	tempGameObjectData.hide = hide;
	tempGameObjectData.alpha = alpha;

	_gameObjectData.push_back(tempGameObjectData);
}

void Render::Hide(bool hide, SDL_Surface* surface)
{
	if(_gameObjectData.size() > 0)
	{
		for(unsigned int i = 0; i < _gameObjectData.size(); i++)
		{
			if(_gameObjectData[i].image == surface)
			{
				_gameObjectData[i].hide = hide;
				break;
			}
		}
	}
}

void Render::AllHide(bool hide)
{
	if(_gameObjectData.size() > 0)
	{
		for(unsigned int i = 0; i < _gameObjectData.size(); i++)
			_gameObjectData[i].hide = hide;
	}
}

Transform::Size Render::GetScreenResolutions()
{
	return GetSize();
}

bool Render::IsLoaded()
{
	return _isLoaded;
}

bool Render::SetWindowInfo(std::string caption, int w, int h, int bpp)
{
	_window = SDL_CreateWindow(caption.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, bpp);
	if (_window == NULL)
	{
		printf("Error: %s\n", SDL_GetError());
		return false;
	}

	Transform::SetSize(w, h);

	_screen = SDL_GetWindowSurface(_window);
	return true;
}

const char* Render::GetFont()
{
	//TODO: Change this to a font of your liking. Make sure it's compatible with Windows and is a .ttf file.
	//NOTE: If you change, don't forget to add font to your project folder.
	return "04B_25__.TTF";
}

void Render::SetBackgroundImage(std::string filename)
{
	AddSurface(_screen, filename, Position().Zero(), false);
}

void Render::SetBackgroundColor(Color color)
{
	_backgroundColor = color;
}

Transform::Color Render::GetBackgroundColor(Color color)
{
	return _backgroundColor;
}

void Render::CleanUp()
{
	if(_gameObjectData.size() > 0)
	{
		for(unsigned int i = 0; i < _gameObjectData.size(); i++)
		{
			GameObjectData tempGameObjectData = _gameObjectData[i];
			if(tempGameObjectData.image != NULL)
				SDL_FreeSurface(tempGameObjectData.image);
		}
		_gameObjectData.clear();
	}
}

void Render::Quit()
{
	CleanUp();
	SDL_DestroyWindow(_window);
	_window = NULL;
}

SDL_Surface* Render::LoadImage(std::string filename)
{
	SDL_Surface* loadedImage = NULL;
	SDL_Surface* optimizedImage = NULL;

	loadedImage = IMG_Load(filename.c_str());

	if(loadedImage != NULL)
	{
		optimizedImage = SDL_ConvertSurfaceFormat(loadedImage, SDL_PIXELFORMAT_RGBA32, 0);
		SDL_FreeSurface(loadedImage);

		if(optimizedImage != NULL)
		{
			SDL_SetColorKey(optimizedImage, SDL_TRUE, SDL_MapRGB(optimizedImage->format, 54, 47, 45));
		}
	}
	else
	{
		_isLoaded = false;
	}

	return optimizedImage;
}

void Render::ApplySurface(SDL_Surface* surface, Position position, SDL_Rect* rect)
{
	SDL_Rect offset;
	offset.x = position.x;
	offset.y = position.y;
	bool hide = false;
	
	for(unsigned int i = 0; i < _gameObjectData.size(); i++)
	{
		GameObjectData tempGameObjectData = _gameObjectData[i];
		if(tempGameObjectData.image == surface)
		{
			if(tempGameObjectData.hide)
				hide = true;
			else
				SDL_SetSurfaceAlphaMod(surface, tempGameObjectData.alpha);
		}
	}

	if(!hide)
		SDL_BlitSurface(surface, rect, _screen, &offset);
}

void Render::UpdateWindowSurface()
{
	SDL_UpdateWindowSurface(_window);
}

void Render::ClearScreen()
{
	SDL_FillRect(_screen, &_screen->clip_rect, SDL_MapRGB(_screen->format, _backgroundColor.r, _backgroundColor.g, _backgroundColor.b));
}
