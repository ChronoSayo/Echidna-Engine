#ifndef RENDER_H_INCLUDED
#define RENDER_H_INCLUDED

#include "SDL_image.h"
#include "Transform.h"
#include <string>
#include <vector>

/*This class organizes and draws all graphics added into the list.*/
class Render : public Transform
{
public:
	static Render* GetInstance();

	Render();
	~Render();

	/*Saves graphics into list to be rendered. Use this once per graphics.*/
	void AddSurface(SDL_Surface* surface, std::string filename, Position position, bool hide, int alpha = SDL_ALPHA_OPAQUE);
	/*Hiding does not remove object; it merely stops rendering it.*/
	void Hide(bool hide, SDL_Surface* surface);
	/*Hiding does not remove object; it merely stops rendering it.*/
	void AllHide(bool hide);
	/*Draws the graphics added into the list. Run this method in Draw().*/
	void ApplySurface(SDL_Surface* surface, Position position, SDL_Rect* rect = NULL);
	/*Updates list of render objects when new values have been added.*/
	void UpdateWindowSurface();
	/*Clears screen every frame.*/
	void ClearScreen();
	SDL_Surface* LoadImage(std::string filename);

	void SetBackgroundImage(std::string filename);
	void SetBackgroundColor(Color color);
	Color Render::GetBackgroundColor(Color color);

	Size GetScreenResolutions();
	bool IsLoaded();
	bool SetWindowInfo(std::string caption, int w, int h, int bpp);
	/*Returns current loaded font.*/
	const char* GetFont();

	void CleanUp();
	void Quit();

private:
	static Render* _staticRender;

	/*Struct is used to keep track of GameObject's render data.*/
	struct GameObjectData
	{
		Position position;
		std::string filename;
		SDL_Surface* image;
		bool hide;
		int alpha;
	};

	SDL_Surface* _screen;
	SDL_Window* _window;
	/*Used for fail safe.*/
	bool _isLoaded;
	int _screenWidth, _screenHeight;
	std::vector<GameObjectData> _gameObjectData;
	Color _backgroundColor;
};

#endif