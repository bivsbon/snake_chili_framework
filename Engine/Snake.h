#pragma once
#include "Board.h"
#include "Fruit.h"
#include "Walls.h"
#include "SpeedUp.h"

class Snake
{
private:
	class Segment
	{
	public:
		void InitHead(const Location& loc);
		void InitBody();
		void InitBody(const Location& in_loc);
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
	void InitBody(const Location& loc, int nSegment);
	void MoveBy(const Location& delta_loc);
	void Grow();
	void Draw(Board& brd) const;
	bool IsEatingWalls(const Board& brd) const;
	bool IsEatingItself();
	bool Eat(const Fruit& apple,const Location& delta_loc) const;
	bool EatWalls(const Walls& wall, const Location& delta_loc) const;
	bool EatSpeedUp(const SpeedUp& spd, const Location& delta_loc) const;
	bool FruitSpawnOn(const Fruit& apple) const;
	Location GetNextLocation(const Location& delta_loc) const;

private:
	static constexpr Color snakeColor = Colors::Yellow;
	static constexpr int nSegmentMax = 500; // I wonder how can anyone reach this score
	Segment segments[nSegmentMax];
	int nSegments = 2;
};