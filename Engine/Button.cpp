#include "Button.h"
#include <cassert>

Button::Button(const Vei2& pos, const int width, const int height, const Font& font, std::string content)
	:
	pos(pos), 
	width(width),
	height(height),
	font(font),
	content(content)
{}

bool Button::mouseHoverOn(const Vei2 & mousePos)
{
	bool trueIfItIs;
	if (trueIfItIs = mousePos.x >= pos.x && mousePos.x < pos.x + width && mousePos.y >= pos.y && mousePos.y < pos.y + height)
	{
		currentColor = colorOnHover;
	}
	else
	{
		currentColor = defaultColor;
	}
	return trueIfItIs;
}

void Button::ColorOnHover(const Color & c)
{
	colorOnHover = c;
}

void Button::Draw(Graphics & gfx)
{
	assert(font.getGlyphWidth() < height - border * 2);
	gfx.Drawbox(pos.x, pos.y, width, height, border, currentColor, borderColor, true);
	const Vei2 middle = pos + Vei2(width, height) / 2;
	const int l = (int)content.length();
	const int textX = middle.x - l * font.getGlyphWidth() / 2;
	const int textY = middle.y - font.getGlyphHeight() / 2;
	font.MyDrawText(content, { textX, textY }, textColor, gfx);
}
