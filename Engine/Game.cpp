/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
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
#include "MainWindow.h"
#include "Game.h"
#include <random>
#include "Snake.h"

Game::Game( MainWindow& wnd )
	:
	wnd(wnd),
	gfx(wnd),
	brd(gfx), 
	rng(rd()),
	freqDist(20, 30),
	nom(L"Sounds\\nom.wav"),
	background(L"Sounds\\soundtrack.wav"),
	dead(L"Sounds\\oof.wav"),
	speedup(L"Sounds\\aaah.wav")
{
	background.Play();
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (!pauseScreen)
	{
		// Keyboard input
		if (wnd.kbd.KeyIsPressed(VK_UP))
			delta_loc = {  0, -1 };
		if (wnd.kbd.KeyIsPressed(VK_DOWN))
			delta_loc = {  0,  1 };
		if (wnd.kbd.KeyIsPressed(VK_LEFT))
			delta_loc = { -1,  0 };
		if (wnd.kbd.KeyIsPressed(VK_RIGHT))
			delta_loc = {  1,  0 };

		// Adjust the frame rate
		const float dt = ft.Mark();
		secondCount += dt;
		if (secondCount >= secondPerMove)
		{
			secondCount = 0;

			// Prevent the snake from running backward
			if (prev_delta_loc.x * delta_loc.x == -1 || prev_delta_loc.y * delta_loc.y == -1)
				delta_loc = prev_delta_loc;
			prev_delta_loc = delta_loc;

			// Eating apple
			if (brd.SnakeEatsApple(delta_loc))
			{
				if (!speedUpMode)
				{
					nom.Play(); // Eating sound
				}
				brd.SnakeGrow();
				score++;
				// Spawn a wall at random place every 2 apples eaten
				if (score % 2 == 0)
				{
					brd.SpawnNewWall();
				}
				// Keep repawning apple if it spawns on snake or walls
				brd.SpawnNewFruit();
			}

			// Gameover scenario
			if (brd.SnakeEatsWalls(delta_loc) || brd.SnakeIsOutside(delta_loc) || brd.SnakeEatsItself(delta_loc))
			{
				gameOver = true;
			}

			// Eating cucumber
			if (brd.SnakeEatSpeedUp(delta_loc))
			{
				cucumber.Terminate();
				secondPerMove = 0.07f;
				speedUpTimer = 0.0f;
				speedUpMode = true;
				pauseScreen = true;
				background.StopAll();
				speedup.StopOne();
				speedup.Play();
			}
			if (!gameOver)
			{
				brd.SnakeMoveBy(delta_loc);
			}
		}

		// Spawn speedup cucumber !!
		if (score && score == fruitPerCucumber && prevScore != score && !cucumber.IsExist())
		{
			fruitPerCucumber = freqDist(rng) + score;
			brd.SpawnSpeedUp();
		}
		if (speedUpMode)
		{
			speedUpTimer += dt;
			if (speedUpTimer >= cucumber.GetDuration())
			{
				speedUpMode = false;
				secondPerMove = 0.15f;
				background.Play();
				loopSoundCounter = 0.0f;
			}
		}
		prevScore = score;

		// Background music
		loopSoundCounter += dt;
		// Plays the background music repeatedly
		if (loopSoundCounter >= soundLength)
		{
			background.Play();
			loopSoundCounter = 0.0f;
		}

		// Sound effects when dead
		if (gameOver)
		{
			background.StopAll();
			speedup.StopAll();
		}

		if (prevGameOver != gameOver)
			dead.Play();

		prevGameOver = gameOver;
	}
	else
	{
		const float dt = ft.Mark();
		pauseCounter += dt;
		if (pauseCounter >= pauseDuration)
		{
			pauseCounter = 0.0f;
			pauseScreen = false;
		}
	}
}

void Game::ComposeFrame()
{
	// Drawing
	if (gameOver)
	{
		fillScreen(255, 0, 0);
	}
	else
	{
		fillScreen(200, 200, 200);
		brd.Draw(gfx);
		DrawScoreBar(score);
	}
}

void Game::fillScreen(int r, int g, int b)
{
	for (int i = 0; i < gfx.ScreenWidth; i++)
		for (int j = 0; j < gfx.ScreenHeight; j++)
			gfx.PutPixel(i, j, r, g, b);
}

void Game::DrawScoreBar(const int score)
{
	float percentage = (float)score / (float)maxScore;
	float w = percentage * 760.0f;
	gfx.drawRectDim(20, 20, (int)w, 30, Colors::Magenta, true);
	//Border
	gfx.drawRectDim(19, 19, 762, 32, Colors::Black, false);
	gfx.drawRectDim(18, 18, 764, 34, Colors::Black, false);
	gfx.drawRectDim(17, 17, 766, 36, Colors::Black, false);
}
