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

int Walls::GetNWalls() const
{
	return nWalls;
}

Location Walls::GetLocation(const int index) const
{
	return walls[index].GetLocation();
}

void Walls::Wall::ChangeLoc(const Location & in_loc)
{
	loc = in_loc;
}

Location Walls::Wall::GetLocation() const
{
	return loc;
}
