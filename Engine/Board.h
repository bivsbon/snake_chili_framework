#pragma once
#include "Graphics.h"
#include "Location.h"

class Board
{
public:
	Board(Graphics& gfx);
	void Draw(Graphics& gfx) const;
	void DrawCell(const Location& loc, Color c) const;
	int GetWidth() const;
	int GetHeight() const;
	bool IsOnBoard(const Location& loc) const;
private:
	static constexpr int margin = 20;
	static constexpr int dimension = 20;
	static constexpr int width = 38;
	static constexpr int height = 26;
	Graphics& gfx;
};