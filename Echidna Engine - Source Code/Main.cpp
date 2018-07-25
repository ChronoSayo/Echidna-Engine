#include "IncludeHell.h"

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 720;
const int SCREEN_PP = 32;

const int FRAMES_PER_SECOND = 60;

SDL_Event _event;

/*Checks if SDL is initiated correctly. Check here if your game isn't running.*/
bool Init()
{
	bool init = true;
	
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		init = false;
	}
	else
	{
		Render::GetInstance()->SetWindowInfo("Echidna Engine", SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_PP);
	}

	if(TTF_Init() == -1)
	{
		init = false;
	}

	if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		init = false;
	}

	return init;
}

/*Application starts from here.*/
int main(int argc, char* args[])
{	
	if(!Init())
	{
		return 0;
	}

	if(!Render::GetInstance()->IsLoaded())
	{
		return 0;
	}
	
	srand((unsigned int)time(NULL));

	Timer delta, fps;
	GameMode gameMode;

	delta.Start();

	bool quit = false;
	while(!quit)
	{
		fps.Start();

		if (gameMode.Quit() || _event.type == SDL_QUIT)
			quit = true;

		while (SDL_PollEvent(&_event))
			Input::GetInstance()->GetSDLInput(_event);

		Render::GetInstance()->ClearScreen();
		
		gameMode.Draw();
		gameMode.Update(delta.GetTicks());

		Render::GetInstance()->UpdateWindowSurface();

		delta.Start();	

		//Locks framerate.
		if(fps.GetTicks() < 1000 / FRAMES_PER_SECOND)
		{
			SDL_Delay(Uint32((1000 / FRAMES_PER_SECOND) - fps.GetTicks()));
		}
	}
	
	Render::GetInstance()->Quit();

	SDL_Quit();

	return 0;
}
