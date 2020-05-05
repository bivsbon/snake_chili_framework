#include "SpeedUp.h"

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

void SpeedUp::Terminate()
{
	exist = false;
	loc.x = -1; //Set it to be outside the screen
}
