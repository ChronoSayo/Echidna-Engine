#include "Mode.h"

Mode::Mode()
{
	//Title placements.
	_textSize = 60;
	_textTag = "text";
	_textPosition = Transform::Position(250, 300);
	Text::GetInstance()->Create("Press Enter To Continue", _textTag, _textPosition, _textSize, Transform::Color().White());

	LoadAudio();
	LoadGraphics();
}

Mode::~Mode()
{
}

void Mode::LoadAudio()
{
}

void Mode::LoadGraphics()
{
}

void Mode::Update(int delta)
{
}

void Mode::Draw()
{
}

bool Mode::Continue()
{
	return Input::GetInstance()->GetKeyReturn() || _continue;
}
