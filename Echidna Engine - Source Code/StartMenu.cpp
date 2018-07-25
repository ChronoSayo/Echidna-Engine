#include "StartMenu.h"

StartMenu::StartMenu() : Mode()
{
	//Title placements.
	Text::GetInstance()->ChangeColor(Transform::Color().Red(), _textTag);
}

StartMenu::~StartMenu()
{
}

void StartMenu::LoadAudio()
{
	Mode::LoadAudio();

	/*TODO: Call Audio and add audio into its list.*/

	//_audio = Audio::GetInstance();
	//_audio->AddSoundFX("audio.wav", "Audio");
}

void StartMenu::LoadGraphics()
{
	Mode::LoadGraphics();

	/*TODO: Call Render and add graphics into its list.*/

	//Render* _render = Render::GetInstance();
	//render->AddSurface(_render->LoadImage("menu background.png"), "background.png", Transform::Position().Zero(), false);
}

void StartMenu::Update(int delta)
{
	Mode::Update(delta);
}

void StartMenu::Draw()
{
	/*TODO: Draw applied graphics here.*/

	//Render::GetInstance()->ApplySurface(_background, Transform::Position().Zero());

	Text::GetInstance()->Draw();
}

bool StartMenu::Continue()
{
	return Mode::Continue();
}