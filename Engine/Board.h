#pragma once
#include "Graphics.h"
#include "Location.h"
#include "Fruit.h"
#include "Snake.h"
#include <vector>
#include <random>
#include "Walls.h"
#include "SpeedUp.h"

class Board
{
public:
	enum CellTypes {
		Air,
		SnakeSeg,
		Apple,
		Wall,
		Cucumber,
		Count
	};
public:
	Board(Graphics& gfx);
	void Draw(Graphics& gfx) const;
	void DrawCell(const Location& loc, Color c) const;
	int GetWidth() const;
	int GetHeight() const;
	void UpdateSnakeLoc();
	bool IsOnBoard(const Location loc) const;
	bool SnakeEatsApple(const Location& delta_loc) const;
	bool SnakeEatsWalls(const Location& delta_loc) const;
	bool SnakeEatSpeedUp(const Location& delta_loc) const;
	bool SnakeIsOutside(const Location& delta_loc) const;
	bool SnakeEatsItself(const Location& delta_loc) const;
	void SpawnNewWall();
	void SpawnNewFruit();
	void SpawnSpeedUp();
	void SnakeGrow();
	void SnakeMoveBy(const Location& delta_loc);
private:
	static constexpr int margin = 20;
	static constexpr int dimension = 20;
	static constexpr int width = 38;
	static constexpr int height = 26;
	Graphics& gfx;
	std::vector<std::vector<CellTypes>> cells;
	// Random stuff
	std::random_device rd;
	std::mt19937 rng;
	std::uniform_int_distribution<int> xDist;
	std::uniform_int_distribution<int> yDist;

	Snake snake;
	Fruit apple;
	Walls walls;
	SpeedUp cucumber;

	Location prevSnakeTail = { 1,1 };
	Location prevSnakeHead = { 2,1 };
};