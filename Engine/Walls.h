#pragma once
#include "Board.h"

class Walls
{
private:
	class Wall
	{
	public:
		void InitWall(const Location& in_loc);
		void Draw(Board& brd) const;
		Location GetLocation() const;
	private:
		Location loc;
		Color c;
	};

public:
	void SpawnNewWall(const Location& in_loc);
	void Draw(Board& brd) const;
	int GetNWalls() const;
	Location GetLocation(const int index) const;

private:
	static constexpr Color wallColor = {100, 100, 100}; // Grey
	static constexpr int nWallMax = 200;
	int nWalls = 0;
	Wall walls[nWallMax];
};