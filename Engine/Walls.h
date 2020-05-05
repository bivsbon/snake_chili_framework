#pragma once
#include <vector>
#include "Location.h"
#include "Colors.h"

class Walls
{
private:
	class Wall
	{
	public:
		Wall(const Location& in_loc);
		void ChangeLoc(const Location& in_loc);
		Location GetLocation() const;
	private:
		Location loc;
	};

public:
	void SpawnNewWall(const Location& in_loc);
	void RespawnWall(const Location& in_loc);
	int GetNWalls() const;
	Location GetLocation(const int index) const;
public:
	static constexpr Color COLOR = { 100, 100, 100 }; // Grey
private:
	int nWalls = 0;
	std::vector<Wall> walls;
};