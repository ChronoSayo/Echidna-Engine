#include "Ending.h"

Ending::Ending() : Mode()
{
	//Title placements.
	Text::GetInstance()->ChangeColor(Transform::Color().Green(), _textTag);
	Text::GetInstance()->Create("Game Over", "gameover",
		_textPosition.x + 200, _textPosition.y + _textSize, _textSize, Transform::Color().Yellow());
}

Ending::~Ending()
{
}

void Ending::LoadAudio()
{
	Mode::LoadAudio();

	/*TODO: Call Audio and add audio into its list.*/

	//_audio = Audio::GetInstance();
	//_audio->AddSoundFX("audio.wav", "Audio");
}

void Ending::LoadGraphics()
{
	Mode::LoadGraphics();

	/*TODO: Call Render and add graphics into its list.*/

	//Render* _render = Render::GetInstance();
	//render->AddSurface(_render->LoadImage("ending background.png"), "background.png", Transform::Position().Zero(), false);
}

void Ending::Update(int delta)
{
	Mode::Update(delta);
}

void Ending::Draw()
{
	/*TODO: Draw applied graphics here.*/

	//Render::GetInstance()->ApplySurface(_background, Transform::Position().Zero());

	Text::GetInstance()->Draw();
}

bool Ending::Continue()
{
	return Mode::Continue();
}
