#include "SpeedUp.h"

void SpeedUp::DrawIfExist(Board& brd) const
{
	brd.DrawCell(loc, c);
}

Location SpeedUp::GetLocation() const
{
	return loc;
}

void SpeedUp::Spawn(const Location in_loc)
{
	loc = in_loc;
	exist = true;
}
