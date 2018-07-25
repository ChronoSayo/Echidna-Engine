#include "Text.h"

Text* Text::_staticText = NULL;

Text::Text()
{
	_dropShadowTag = "%S";
	_dropShadowX = 2;
	_dropShadowY = 2;
}

Text::~Text()
{
	RemoveAll();
}

Text* Text::GetInstance()
{
	if(_staticText == NULL)
	{
		_staticText = new Text();
	}

	return _staticText;
}

void Text::Create(std::string text, std::string tag, Transform::Position position, int size, Transform::Color color, 
	bool hide, bool dropShadow)
{
	Create(text, tag, position.x, position.y, size, color, hide, dropShadow);
}

void Text::Create(std::string text, std::string tag, int x, int y, int size, Transform::Color color, bool hide, bool dropShadow)
{
	TextData tempTextData;
	tempTextData.text = Capitalize(text);
	tempTextData.tag = tag;
	tempTextData.size = size;
	tempTextData.font = TTF_OpenFont(Render::GetInstance()->GetFont(), tempTextData.size);
	tempTextData.position = Transform::Position(x, y);
	tempTextData.color = color;
	tempTextData.surface = TTF_RenderText_Solid(tempTextData.font, tempTextData.text.c_str(), GetSDLColor(color.r, color.g, color.b));
	tempTextData.hide = hide;
	tempTextData.dropShadow = dropShadow;

	if(dropShadow)
	{
		_textData.push_back(CreateDropShadow(text, tag, x, y, size, color, hide));
		_textData.push_back(tempTextData);
	}
	else
		_textData.push_back(tempTextData);

}

Text::TextData Text::CreateDropShadow(std::string text, std::string tag, int x, int y, 
	int size, Transform::Color color, bool hide)
{
	TextData tempTextData;
	tempTextData.text = Capitalize(text);
	tempTextData.tag = tag + _dropShadowTag;
	tempTextData.size = size;
	tempTextData.font = TTF_OpenFont(Render::GetInstance()->GetFont(), tempTextData.size);
	tempTextData.position = Transform::Position(x + _dropShadowX, y + _dropShadowY);
	tempTextData.color = color;
	tempTextData.surface = TTF_RenderText_Solid(tempTextData.font, tempTextData.text.c_str(), GetSDLColor(color.r, color.g, color.b));
	tempTextData.hide = hide;
	tempTextData.dropShadow = true;

	return tempTextData;
}

void Text::ChangeText(std::string newText, std::string tag)
{
	bool dropShadow = false;
	TextData tempTextData;
	if(FindByTag(tag, tempTextData))
	{
		tempTextData.text = Capitalize(newText);
		dropShadow = tempTextData.dropShadow;
		UpdateTextData(tempTextData);
	}
	if(dropShadow && FindByTag(tag + _dropShadowTag, tempTextData))
	{
		tempTextData.text = Capitalize(newText);
		UpdateTextData(tempTextData);
	}
}

void Text::ChangePosition(Transform::Position newPosition, std::string tag)
{
	bool dropShadow = false;
	TextData tempTextData;
	if(FindByTag(tag, tempTextData))
	{
		tempTextData.position = newPosition;
		dropShadow = tempTextData.dropShadow;
		UpdateTextData(tempTextData);
	}
	if(dropShadow && FindByTag(tag + _dropShadowTag, tempTextData))
	{
		tempTextData.position = Transform::Position(newPosition.x + _dropShadowX, newPosition.y + _dropShadowY);
		UpdateTextData(tempTextData);
	}
}

void Text::ChangePosition(int x, int y, std::string tag)
{
	bool dropShadow = false;
	TextData tempTextData;
	if(FindByTag(tag, tempTextData))
	{
		tempTextData.position = Transform::Position(x, y);
		dropShadow = tempTextData.dropShadow;
		UpdateTextData(tempTextData);
	}
	if(dropShadow && FindByTag(tag + _dropShadowTag, tempTextData))
	{
		tempTextData.position = Transform::Position(x + _dropShadowX, y + _dropShadowY);
		UpdateTextData(tempTextData);
	}
}

void Text::ChangePositionX(int x, std::string tag)
{
	bool dropShadow = false;
	TextData tempTextData;
	if(FindByTag(tag, tempTextData))
	{
		tempTextData.position = Transform::Position(x, tempTextData.position.y);
		dropShadow = tempTextData.dropShadow;
		UpdateTextData(tempTextData);
	}
	if(dropShadow && FindByTag(tag + _dropShadowTag, tempTextData))
	{
		tempTextData.position = Transform::Position(x + _dropShadowX, tempTextData.position.y);
		UpdateTextData(tempTextData);
	}
}

void Text::ChangePositionY(int y, std::string tag)
{
	bool dropShadow = false;
	TextData tempTextData;
	if(FindByTag(tag, tempTextData))
	{
		tempTextData.position = Transform::Position(tempTextData.position.x, y);
		dropShadow = tempTextData.dropShadow;
		UpdateTextData(tempTextData);
	}
	if(dropShadow && FindByTag(tag + _dropShadowTag, tempTextData))
	{
		tempTextData.position = Transform::Position(tempTextData.position.x, y + _dropShadowY);
		UpdateTextData(tempTextData);
	}
}

void Text::ChangeSize(int newSize, std::string tag)
{
	TextData tempTextData;
	if(FindByTag(tag, tempTextData))
	{
		tempTextData.size = newSize;
		//Reloading the font is the only way to change the size of the text.
		tempTextData.font = TTF_OpenFont("Font/04B_25__.TTF", tempTextData.size);
		UpdateTextData(tempTextData);
	}
}

void Text::ChangeColor(Transform::Color newColor, std::string tag)
{
	TextData tempTextData;
	if(FindByTag(tag, tempTextData))
	{
		tempTextData.color = newColor;
		UpdateTextData(tempTextData);
	}
}

void Text::ChangeDropShadowColor(Transform::Color newColor, std::string mainTag)
{
	TextData tempTextData;
	if(FindByTag(mainTag + _dropShadowTag, tempTextData))
	{
		tempTextData.color = newColor;
		UpdateTextData(tempTextData);
	}
}

void Text::ChangeVisibility(bool hide, std::string tag)
{
	bool dropShadow = false;
	TextData tempTextData;
	if(FindByTag(tag, tempTextData))
	{
		tempTextData.hide = hide;
		dropShadow = tempTextData.dropShadow;
		UpdateTextData(tempTextData);
	}
	if(dropShadow && FindByTag(tag + _dropShadowTag, tempTextData))
	{
		tempTextData.hide = hide;
		UpdateTextData(tempTextData);
	}
}
	
bool Text::GetVisibility(std::string tag)
{
	bool b = false;
	TextData tempTextData;
	if(FindByTag(tag, tempTextData))
	{
		b = tempTextData.hide;
	}
	return b;
}

Transform::Color Text::GetColor(std::string tag)
{
	Transform::Color c = Transform::Color().Black();
	TextData tempTextData;
	if(FindByTag(tag, tempTextData))
	{
		c = tempTextData.color;
	}
	return c;
}

void Text::EnableDropShadow(bool enable, std::string tag)
{
	TextData tempTextData;
	if(FindByTag(tag, tempTextData))
	{
		tempTextData.dropShadow = enable;
		UpdateTextData(tempTextData);
	}
	if(FindByTag(tag + _dropShadowTag, tempTextData))
	{
		tempTextData.hide = enable;
		UpdateTextData(tempTextData);
	}
}

void Text::Remove(std::string tag)
{
	TextData tempTextData;
	int found = -1;
	if(FindByTag(tag, tempTextData))
	{
		for(unsigned int i = 0; i < _textData.size(); i++)
		{
			if(_textData[i].tag == tempTextData.tag)
			{
				found = i;
				break;
			}
		}
	}

	if(found != -1)
		_textData.erase(_textData.begin() + found);
}

void Text::RemoveAll()
{
	if(_textData.size() > 0)
	{
		_textData.clear();
	}
}

std::string Text::Capitalize(std::string s)
{
	std::locale loc;
	for (unsigned int i = 0; i < s.size(); i++)
		s[i] = std::toupper(s[i], loc);

	return s;
}

std::string Text::IntToString(int i)
{
	return std::to_string((long long)i);
}


int Text::StringToInt(std::string s)
{
	return atoi(s.c_str());
}

void Text::Draw()
{
	if(_textData.size() <= 0)
		return;

	for(unsigned int i = 0; i < _textData.size(); i++)
	{
		if(!_textData[i].hide)
			Render::GetInstance()->ApplySurface(_textData[i].surface, _textData[i].position, NULL);
	}
}

SDL_Color Text::GetSDLColor(int r, int g, int b)
{
	SDL_Color c = {Uint8(r), Uint8(g), Uint8(b)};
	return c;
}

void Text::UpdateTextData(TextData textData)
{
	if(_textData.size() <= 0)
		return;
	
	TextData tempTextData;
	tempTextData.text = textData.text;
	tempTextData.tag = textData.tag;
	tempTextData.size = textData.size;
	tempTextData.font = textData.font;
	tempTextData.position = textData.position;
	tempTextData.color = textData.color;
	tempTextData.surface = TTF_RenderText_Solid(tempTextData.font, tempTextData.text.c_str(), 
		GetSDLColor(textData.color.r, textData.color.g, textData.color.b));
	tempTextData.hide = textData.hide;
	tempTextData.dropShadow = textData.dropShadow;

	for(unsigned int i = 0; i < _textData.size(); i++)
	{
		if(_textData[i].tag == textData.tag)
		{
			_textData[i] = tempTextData;
			break;
		}
	}

}

bool Text::FindByTag(std::string tag, TextData& textData)
{
	if(_textData.size() <= 0)
		return false;

	for(unsigned int i = 0; i < _textData.size(); i++)
	{
		TextData tempTextData = _textData[i];
		if(tempTextData.tag == tag)
		{
			textData = _textData[i];
			return true;
		}
	}
	return false;
}