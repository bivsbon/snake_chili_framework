#include "Snake.h"

using namespace std;

Snake::Snake()
{
	segments.emplace_back(Segment({ 2,1 }, Snake::COLOR));
	segments.emplace_back(Segment({ 1,1 }, Snake::COLOR));
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
	segments.emplace_back(Segment(COLOR));
	nSegments++;
}

Location Snake::GetNextLocation(const Location & delta_loc) const
{
	Location l = segments[0].GetLocation();
	l.Add(delta_loc);
	return l;
}

Location Snake::Tail() const
{
	return segments[nSegments-1].GetLocation();
}

Location Snake::Head() const
{
	return segments[0].GetLocation();
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

Location Snake::Segment::GetLocation() const
{
	return loc;
}
