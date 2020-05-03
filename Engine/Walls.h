#pragma once
#include "Board.h"
#include "vector"

class Walls
{
private:
	class Wall
	{
	public:
		Wall(const Location& in_loc);
		void ChangeLoc(const Location& in_loc);
		void Draw(Board& brd) const;
		Location GetLocation() const;
		static constexpr Color c = { 100, 100, 100 }; // Grey
	private:
		Location loc;
	};

public:
	void SpawnNewWall(const Location& in_loc);
	void RespawnWall(const Location& in_loc);
	void Draw(Board& brd) const;
	int GetNWalls() const;
	Color GetWallColor() const;
	Location GetLocation(const int index) const;

private:
	int nWalls = 0;
	std::vector<Wall> walls;
};