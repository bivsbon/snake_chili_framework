#pragma once
#include "Board.h"
#include "Fruit.h"
#include "Walls.h"
#include "SpeedUp.h"
#include <vector>

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
		void Draw(Board& brd) const;
		Location GetLocation() const;
	private:
		Location loc;
		Color c;
	};

public:
	Snake(const Location& in_loc);
	void MoveBy(const Location& delta_loc);
	void Grow();
	void Draw(Board& brd) const;
	bool IsEatingWalls(const Board& brd) const;
	bool IsEatingItself();
	bool Eat(const Fruit& apple,const Location& delta_loc) const;
	bool EatWalls(const Walls& wall, const Location& delta_loc) const;
	bool WallSpawnOn(const Walls& wall) const;
	bool EatSpeedUp(const SpeedUp& spd, const Location& delta_loc) const;
	bool FruitSpawnOn(const Fruit& apple) const;
	Location GetNextLocation(const Location& delta_loc) const;

private:
	static constexpr Color snakeColor = Colors::Yellow;
	std::vector<Segment> segments;
	int nSegments = 2;
};