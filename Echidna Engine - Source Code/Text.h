#ifndef TEXT_H_INCLUDED
#define TEXT_H_INCLUDED

#include <locale>
#include "SDL_ttf.h"
#include "Render.h"

/*Use this class to display text on screen. Initialize it by giving it a tag. This class draws everything in its list.*/
class Text
{
public:
	static Text* GetInstance();

	Text();
	~Text();

	/*Creates the text component. Run this once to load up the text. Use the tag to update the text's data.*/
	void Create(std::string text, std::string tag, Transform::Position position, int size, Transform::Color color, 
		bool hide = false, bool dropShadow = false);
	/*Creates the text component. Run this once to load up the text. Use the tag to update the text's data.*/
	void Create(std::string text, std::string tag, int x, int y, int size, Transform::Color color, bool hide = false, 
		bool dropShadow = false);

	void ChangeText(std::string newText, std::string tag);
	void ChangePosition(Transform::Position newPosition, std::string tag);
	void ChangePosition(int x, int y, std::string tag);
	void ChangePositionX(int x, std::string tag);
	void ChangePositionY(int y, std::string tag);
	void ChangeSize(int p_NewSize, std::string tag);
	void ChangeColor(Transform::Color newColor, std::string tag);
	void ChangeDropShadowColor(Transform::Color newColor, std::string mainTag);
	void ChangeVisibility(bool hide, std::string tag);
	/*This method can be used to create outlines.*/
	void EnableDropShadow(bool enable, std::string tag);

	/*Returns true if text is visible.*/
	bool GetVisibility(std::string tag);
	Transform::Color GetColor(std::string tag);

	void Remove(std::string tag);
	void RemoveAll();

	std::string Capitalize(std::string s);
	std::string IntToString(int i);
	int StringToInt(std::string s);

	void Draw();

private:
	static Text* _staticText;

	/*Text data. Makes it easier to customize.*/
	struct TextData
	{
		SDL_Surface* surface;
		TTF_Font* font;
		std::string text;
		std::string tag;
		Transform::Position position;
		Transform::Color color;
		int size;
		bool hide;
		bool dropShadow;

		TextData()
		{
			surface = NULL;
			font = NULL;
		}
	};

	//Drop-shadow data.
	std::string _dropShadowTag;
	int _dropShadowX, _dropShadowY;

	SDL_Color GetSDLColor(int r, int g, int b);
	void UpdateTextData(TextData textData);
	bool FindByTag(std::string tag, TextData& textData);

	TextData CreateDropShadow(std::string text, std::string tag, int x, int y, int size, Transform::Color color, bool hide);

	std::vector<TextData> _textData;
};

#endif