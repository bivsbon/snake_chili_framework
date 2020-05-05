#include "Board.h"
#include <assert.h>

using namespace std;

Board::Board(Graphics& gfx)
	:
	gfx(gfx),
	rng(rd()),
	xDist(0, width-1), 
	yDist(0, height-1),
	apple({xDist(rng), yDist(rng)})
{
	for (int i = 0; i < width; ++i)
	{
		vector<CellTypes> temp;
		for (int j = 0; j < height; ++j)
		{
			temp.push_back(CellTypes::Air);
		}
		cells.push_back(temp);
	}
	cells[2][1] = CellTypes::SnakeSeg;
	cells[1][1] = CellTypes::SnakeSeg;
	cells[apple.GetLocation().x][apple.GetLocation().y] = CellTypes::Apple;
}

void Board::Draw(Graphics & gfx) const
{
	int x = margin;
	int y = gfx.ScreenHeight - margin - height * dimension;
	int w = dimension * width;
	int h = dimension * height;
	gfx.drawRectDim(x-1, y-1, w+2, h+2, Colors::Blue, false);
	gfx.drawRectDim(x-2, y-2, w+4, h+4, Colors::Blue, false);
	gfx.drawRectDim(x-3, y-3, w+6, h+6, Colors::Blue, false);

	for (int i = 0; i < width; ++i)
	{
		for (int j = 0; j < height; ++j)
		{
			switch (cells[i][j])
			{
			case CellTypes::SnakeSeg:
				DrawCell({ i, j }, Snake::COLOR);
				break;
			case CellTypes::Wall:
				DrawCell({ i, j }, Walls::COLOR);
				break;
			case CellTypes::Apple:
				DrawCell({ i, j }, Fruit::COLOR);
				break;
			case CellTypes::Cucumber:
				DrawCell({ i, j }, SpeedUp::COLOR);
				break;
			}
		}
	}
}

void Board::DrawCell(const Location& loc, Color c) const
{
	assert(loc.x >= 0);
	assert(loc.x < width);
	assert(loc.y >= 0);
	assert(loc.y < height);
	Location drawLoc = { loc.x + 1, loc.y + 3 };
	gfx.drawRectDim(drawLoc.x*dimension+2, drawLoc.y*dimension+2, dimension-4, dimension-4, c, true);
	gfx.drawRectDim(drawLoc.x*dimension+1, drawLoc.y*dimension+1, dimension-2, dimension-2, Colors::Black, false);
}

int Board::GetWidth() const
{
	return width;
}

int Board::GetHeight() const
{
	return height;
}

void Board::UpdateSnakeLoc()
{
	cells[prevSnakeTail.x][prevSnakeTail.y] = CellTypes::Air;
	cells[snake.Tail().x][snake.Tail().y] = CellTypes::SnakeSeg;
	cells[snake.Head().x][snake.Head().y] = CellTypes::SnakeSeg;
	prevSnakeTail = snake.Tail();
	prevSnakeHead = snake.Head();
}

bool Board::IsOnBoard(const Location loc) const
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

bool Board::SnakeEatsApple(const Location& delta_loc) const
{
	return snake.GetNextLocation(delta_loc) == apple.GetLocation();
}

bool Board::SnakeEatsWalls(const Location & delta_loc) const
{
	auto nextSnakeHead = snake.GetNextLocation(delta_loc);
	auto n = walls.GetNWalls();

	for (int i = 0; i < n; i++)
	{
		if (nextSnakeHead == walls.GetLocation(i))
		{
			return true;
		}
	}
	return false;
}

bool Board::SnakeEatSpeedUp(const Location & delta_loc) const
{
	return snake.GetNextLocation(delta_loc) == cucumber.GetLocation();
}

bool Board::SnakeIsOutside(const Location& delta_loc) const
{
	return !IsOnBoard(snake.GetNextLocation(delta_loc));
}

bool Board::SnakeEatsItself(const Location & delta_loc) const
{
	auto nextLoc = snake.GetNextLocation(delta_loc);
	int x = nextLoc.x, y = nextLoc.y;
	return cells[x][y] == CellTypes::SnakeSeg;
}

void Board::SpawnNewWall()
{
	int x, y;
	// Generate a new wall location until it's not on any object
	do
	{
		x = xDist(rng);
		y = yDist(rng);
	} while (cells[x][y] != CellTypes::Air);
	walls.SpawnNewWall({ x, y });
	cells[x][y] = CellTypes::Wall;
}

void Board::SpawnNewFruit()
{
	int x, y;
	// Generate a new fruit location until it's not on any object
	do
	{
		x = xDist(rng);
		y = yDist(rng);
	} while (cells[x][y] != CellTypes::Air);
	apple.Spawn({ x, y });
	cells[x][y] = CellTypes::Apple;
}

void Board::SpawnSpeedUp()
{
	int x, y;
	// Generate a new speedup location until it's not on any object
	do
	{
		x = xDist(rng);
		y = yDist(rng);
	} while (cells[x][y] != CellTypes::Air);
	cucumber.Spawn({ x, y });
	cells[x][y] = CellTypes::Cucumber;
}

void Board::SnakeGrow()
{
	snake.Grow();
}

void Board::SnakeMoveBy(const Location& delta_loc)
{
	snake.MoveBy(delta_loc);
	UpdateSnakeLoc();
}
