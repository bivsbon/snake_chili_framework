/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Board.h"
#include "Snake.h"
#include "Fruit.h"
#include "Walls.h"
#include <random>
#include "FrameTimer.h"
#include "Sound.h"
#include "SpeedUp.h"

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	void fillScreen(int r, int g, int b);
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	FrameTimer ft;
	std::random_device rd;
	std::mt19937 rng;
	std::uniform_int_distribution<int> xDist;
	std::uniform_int_distribution<int> yDist;
	std::uniform_int_distribution<int> freqDist;

	Board brd;
	Fruit apple;
	Snake snake;
	Walls walls;
	SpeedUp cucumber;

	float secondPerMove = 0.15f;
	float secondCount = 0.0f;
	Location delta_loc = { 0, 0 };
	Location prev_delta_loc = delta_loc;
	bool gameOver = false;
	bool prevGameOver = false;
	int score = 0;
	int prevScore = 0;
	float speedUpTimer= 0.0f;
	bool speedUpMode = false;
	bool pauseScreen = false;
	int fruitPerCucumber = 5;
	float pauseCounter = 0.0f;
	static constexpr float pauseDuration = 3.25f;

	Sound nom;
	Sound background;
	Sound dead;
	Sound speedup;
	float loopSoundCounter = 0.0f;
	static constexpr float soundLength = 249.0f;
	/********************************/
};