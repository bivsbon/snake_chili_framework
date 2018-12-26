#include "Fruit.h"

void Fruit::Init(const Location& in_loc)
{
	loc = in_loc;
}

void Fruit::Respawn(const Location& new_loc)
{
	loc = new_loc;
}

void Fruit::Draw(Board & brd)
{
	brd.DrawCell(loc, c);
}

Location Fruit::GetLocation() const
{
	return loc;
}
