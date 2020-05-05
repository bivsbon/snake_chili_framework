#pragma once
#include "Location.h"
#include "Colors.h"

class Fruit
{
public:
	Fruit(const Location& in_loc);
	void Spawn(const Location& loc);
	Location GetLocation() const;
public:
	static constexpr Color COLOR = Colors::Red;
private:
	Location loc;
};