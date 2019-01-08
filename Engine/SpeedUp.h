#pragma once
#include "Board.h"

class SpeedUp
{
public:
	void DrawIfExist(Board& brd) const;
	Location GetLocation() const;
	void Spawn(const Location in_loc);
	void Terminate();
private:
	bool exist = false;
	Location loc;
	static constexpr Color c = Colors::Green;
	float duration = 5.0f;
};
