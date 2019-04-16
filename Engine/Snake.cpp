#include "Snake.h"

using namespace std;

Snake::Snake(const Location& loc)
{
	segments.emplace_back(Segment(loc, snakeColor));
	segments.emplace_back(Segment({loc.x - 1, loc.y}, snakeColor));
}

void Snake::MoveBy(const Location& delta_loc)
{
	for (int i = nSegments - 1; i > 0; --i)
	{
		segments[i].Follow(segments[i - 1]);
	}
	segments[0].MoveBy(delta_loc);
}

void Snake::Grow()
{
	segments.emplace_back(Segment(snakeColor));
	nSegments++;
}

void Snake::Draw(Board& brd) const
{
	for (int i = 0; i < nSegments; i++)
		segments[i].Draw(brd);
}

bool Snake::IsEatingWalls(const Board& brd) const
{
	if (brd.IsOnBoard(segments[0].GetLocation()))
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool Snake::IsEatingItself()
{
	for (int i = 1; i < nSegments; i++)
	{
		if (segments[0].GetLocation() == segments[i].GetLocation())
			return true;
	}
	return false;
}

bool Snake::FruitSpawnOn(const Fruit& apple) const
{
	for (int i = 0; i < nSegments; i++)
	{
		if (segments[i].GetLocation() == apple.GetLocation())
		{
			return true;
		}
		else
			;
	}
	return false;
}

Location Snake::GetNextLocation(const Location & delta_loc) const
{
	Location l = segments[0].GetLocation();
	l.Add(delta_loc);
	return l;
}

bool Snake::Eat(const Fruit& apple,const Location& delta_loc) const
{
	if (GetNextLocation(delta_loc) == apple.GetLocation())
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Snake::EatWalls(const Walls& wall, const Location & delta_loc) const
{
	for (int i = 0; i < wall.GetNWalls(); i++)
	{
		if (GetNextLocation(delta_loc) == wall.GetLocation(i))
		{
			return true;
		}
		else
			;
	}
	return false;
}

bool Snake::WallSpawnOn(const Walls& wall) const
{
	for (int i = 0; i < nSegments; i++)
	{
		if (segments[i].GetLocation() == wall.GetLocation(wall.GetNWalls() - 1))
		{
			return true;
		}
		else
			;
	}
	return false;
}

bool Snake::EatSpeedUp(const SpeedUp & spd, const Location & delta_loc) const
{
	if (GetNextLocation(delta_loc) == spd.GetLocation())
	{
		return true;
	}
	else
	{
		return false;
	}
}

Snake::Segment::Segment(Location loc, Color c)
	:
	loc(loc),
	c(c)
{}

Snake::Segment::Segment(Color c)
	:
	c(c)
{}

void Snake::Segment::MoveBy(const Location& delta_loc)
{
	loc.Add(delta_loc);
}

void Snake::Segment::Follow(const Segment & next)
{
	loc = next.loc;
}

void Snake::Segment::Draw(Board & brd) const
{
	brd.DrawCell(loc, c);
}

Location Snake::Segment::GetLocation() const
{
	return loc;
}
