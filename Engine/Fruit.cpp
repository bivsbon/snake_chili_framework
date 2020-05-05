#include "Fruit.h"

Fruit::Fruit(const Location& in_loc)
	:
	loc(in_loc)
{}

void Fruit::Spawn(const Location& new_loc)
{
	loc = new_loc;
}

Location Fruit::GetLocation() const
{
	return loc;
}
