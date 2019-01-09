#include "Board.h"
#include <assert.h>

Board::Board(Graphics& gfx)
	:
	gfx(gfx)
{
}

void Board::Draw(Graphics & gfx)
{
	int x = margin;
	int y = gfx.ScreenHeight - margin - height * dimension;
	int w = dimension * width;
	int h = dimension * height;
	gfx.drawRectDim(x-1, y-1, w+2, h+2, Colors::Blue, false);
	gfx.drawRectDim(x-2, y-2, w+4, h+4, Colors::Blue, false);
	gfx.drawRectDim(x-3, y-3, w+6, h+6, Colors::Blue, false);
}

void Board::DrawCell(const Location& loc, Color c)
{
	assert(loc.x >= 0);
	assert(loc.x < width);
	assert(loc.y >= 0);
	assert(loc.y < height);
	Location drawLoc = Location{loc.x + 1, loc.y + 3};
	gfx.drawRectDim(drawLoc.x*dimension+2, drawLoc.y*dimension+2, dimension-4, dimension-4, c, true);
	gfx.drawRectDim(drawLoc.x*dimension+1, drawLoc.y*dimension+1, dimension-2, dimension-2, Colors::Black, false);
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
