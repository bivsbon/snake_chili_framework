#include "Special.h"

void Special::SpawnNewWall(const Location & in_loc)
{
	walls[nWalls].InitWall(in_loc);
	nWalls++;
}

void Special::Draw(Board& brd) const
{
	for (int i = 0; i < nWalls; i++)
	{
		walls[i].Draw(brd);
	}
}

bool Special::FoodSpawnOn(const Fruit & apple) const
{
	return false;
}

void Special::Wall::InitWall(const Location& in_loc)
{
	loc = in_loc;
	c = wallColor;
}

void Special::Wall::Draw(Board& brd) const
{
	brd.DrawCell(loc, c);
}
