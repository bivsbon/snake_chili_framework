#pragma once
#include "Board.h"

class Fruit
{
public:
	void Init(const Location& in_loc);
	void Respawn(const Location& loc);
	void Draw(Board& brd);
	Location GetLocation() const;
private:
	Location loc;
	static constexpr Color c = Colors::Red;
};