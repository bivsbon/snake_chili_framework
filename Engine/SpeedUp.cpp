#include "SpeedUp.h"

void SpeedUp::Draw(Board& brd) const
{
	brd.DrawCell(loc, c);
}

Location SpeedUp::GetLocation() const
{
	return loc;
}

float SpeedUp::GetDuration() const
{
	return duration;
}

void SpeedUp::Spawn(const Location in_loc)
{
	loc = in_loc;
	exist = true;
}

bool SpeedUp::IsExist() const
{
	return exist;
}

bool SpeedUp::SpawnOnWalls(const Walls & wall) const
{
	for (int i = 0; i < wall.GetNWalls(); i++)
	{
		if (GetLocation() == wall.GetLocation(i))
		{
			return true;
		}
		else
			;
	}
	return false;
}

void SpeedUp::Terminate()
{
	exist = false;
	loc.x = -1; //Set it to be outside the screen
}
