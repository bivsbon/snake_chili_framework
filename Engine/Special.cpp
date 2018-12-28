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

int Special::GetNWalls() const
{
	return nWalls;
}

Location Special::GetLocation(const int index) const
{
	return walls[index].GetLocation();
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

Location Special::Wall::GetLocation() const
{
	return loc;
}
