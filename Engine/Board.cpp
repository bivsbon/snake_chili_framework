#include "Board.h"
#include <assert.h>

Board::Board(Graphics& gfx)
	:
	gfx(gfx)
{
}

void Board::DrawCell(const Location & loc, Color c)
{
	assert(loc.x >= 0);
	assert(loc.x < width);
	assert(loc.y >= 0);
	assert(loc.y < height);
	gfx.drawRectDim(loc.x*dimension+2, loc.y*dimension+2, dimension-4, dimension-4, c, true);
	gfx.drawRectDim(loc.x*dimension+1, loc.y*dimension+1, dimension-2, dimension-2, Colors::Black, false);
}

int Board::GetWidth()
{
	return width;
}

int Board::GetHeight()
{
	return height;
}

bool Board::IsOnBoard(const Location & loc) const
{
	if (loc.x < 0 || loc.x >= width ||
		loc.y < 0 || loc.y >= height)
	{
		return false;
	}
	else
	{
		return true;
	}
}
