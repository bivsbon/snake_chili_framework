#include "Walls.h"

void Walls::SpawnNewWall(const Location & in_loc)
{
	walls[nWalls].InitWall(in_loc);
	nWalls++;
}

void Walls::Draw(Board& brd) const
{
	for (int i = 0; i < nWalls; i++)
	{
		walls[i].Draw(brd);
	}
}

int Walls::GetNWalls() const
{
	return nWalls;
}

Location Walls::GetLocation(const int index) const
{
	return walls[index].GetLocation();
}

void Walls::Wall::InitWall(const Location& in_loc)
{
	loc = in_loc;
	c = wallColor;
}

void Walls::Wall::Draw(Board& brd) const
{
	brd.DrawCell(loc, c);
}

Location Walls::Wall::GetLocation() const
{
	return loc;
}
