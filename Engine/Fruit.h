#pragma once
#include "Board.h"
#include "Walls.h"
#include "SpeedUp.h"

class Fruit
{
public:
	void Init(const Location& in_loc);
	void Respawn(const Location& loc);
	void Draw(Board& brd) const;
	Location GetLocation() const;
	bool SpawnOnWalls(const Walls& wall) const;
private:
	Location loc;
	static constexpr Color c = Colors::Red;
};