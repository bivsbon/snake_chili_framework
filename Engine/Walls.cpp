#include "Walls.h"

Walls::Wall::Wall(const Location& in_loc)
	:
	loc(in_loc)
{}

void Walls::SpawnNewWall(const Location & in_loc)
{
	walls.push_back(Wall(in_loc));
	nWalls++;
}

void Walls::RespawnWall(const Location & in_loc)
{
	walls[nWalls - 1].ChangeLoc(in_loc);
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

Color Walls::GetWallColor() const
{
	return Wall::c;
}

Location Walls::GetLocation(const int index) const
{
	return walls[index].GetLocation();
}

void Walls::Wall::ChangeLoc(const Location & in_loc)
{
	loc = in_loc;
}

void Walls::Wall::Draw(Board& brd) const
{
	brd.DrawCell(loc, c);
}

Location Walls::Wall::GetLocation() const
{
	return loc;
}
