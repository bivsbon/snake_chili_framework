#pragma once
#include <vector>
#include "Location.h"
#include "Colors.h"

class Snake
{
private:
	class Segment
	{
	public:
		Segment(Location loc, Color c);
		Segment(Color c);
		void MoveBy(const Location& delta_loc);
		void Follow(const Segment& next);
		Location GetLocation() const;
	private:
		Location loc;
		Color c;
	};
public:
	Snake();
	void MoveBy(const Location& delta_loc);
	void Grow();
	Location GetNextLocation(const Location& delta_loc) const;
	Location Tail() const;
	Location Head() const;
public:
	static constexpr Color COLOR = Colors::Yellow;
private:
	std::vector<Segment> segments;
	int nSegments = 2;
};