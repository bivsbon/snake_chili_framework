#pragma once
#include "Vei2.h"
#include <string>
#include "Graphics.h"
#include "Colors.h"
#include "Font.h"

class Button
{
public:
	Button() = default;
	Button(const Vei2& pos, const int width, const int height, const Font& font, std::string content);
	bool mouseHoverOn(const Vei2& mousePos);
	void ColorOnHover(const Color& c);
	void Draw(Graphics& gfx);
private:
	Vei2 pos;
	int width, height;
	Font font;
	std::string content;
	Color defaultColor = Colors::LightGray;
	Color currentColor = defaultColor;
	Color colorOnHover = Colors::Yellow;
	Color borderColor = Colors::Black;
	Color textColor = Colors::Black;
	static constexpr int border = 2;
};

