#pragma once
#include "Board.h"
#include "Fruit.h"
#include "Special.h"

class Snake
{
private:
	class Segment
	{
	public:
		void InitHead(const Location& loc);
		void InitBody();
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
	bool EatSpecial(const Special& wall,const Location& delta_loc) const;
	bool FruitSpawnOn(const Fruit& apple) const;
	Location GetNextLocation(const Location& delta_loc) const;

private:
	static constexpr Color snakeColor = Colors::Yellow;
	static constexpr int nSegmentMax = 1200; // I wonder how can anyone reach this score
	Segment segments[nSegmentMax];
	int nSegments = 1;
};