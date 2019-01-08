#pragma once
#include "Board.h"
#include "Walls.h"

class SpeedUp
{
public:
	void Draw(Board& brd) const;
	Location GetLocation() const;
	float GetDuration() const;
	void Spawn(const Location in_loc);
	bool IsExist() const;
	bool SpawnOnWalls(const Walls& wall) const;
	void Terminate();

private:
	bool exist = false;
	Location loc;
	static constexpr Color c = Colors::Green;
	float duration = 35.0f;
};
