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
	snake({1, 1}),
	xDist(0, 39),
	yDist(0, 29)	
{
	//apple.Init({ xDist(rng), yDist(rng) });
	apple.Init({ 0, 14});
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
	// Keyboard input
	if (wnd.kbd.KeyIsPressed(VK_UP))
		delta_loc = {  0, -1 };
	if (wnd.kbd.KeyIsPressed(VK_DOWN))
		delta_loc = {  0,  1 };
	if (wnd.kbd.KeyIsPressed(VK_LEFT))
		delta_loc = { -1,  0 };
	if (wnd.kbd.KeyIsPressed(VK_RIGHT))
		delta_loc = {  1,  0 };

	// Prevent the snake from running backward
	if (prev_delta_loc.x * delta_loc.x == -1 || prev_delta_loc.y * delta_loc.y == -1)
		delta_loc = prev_delta_loc;
	prev_delta_loc = delta_loc;

	// Adjust the frame rate
	frameCount++;
	if (frameCount == framePerMove)
	{
		frameCount = 0;

		if (snake.Eat(apple, delta_loc))
		{
			snake.Grow();
			do
			{
				apple.Respawn({ xDist(rng), yDist(rng) });
			} while (snake.FruitSpawnOn(apple));
		}
		snake.MoveBy(delta_loc);
	}

	// Gameover scenarios
	if (snake.IsEatingWalls(brd) || snake.IsEatingItself())
	{
		gameOver = true;
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
		snake.Draw(brd);
		apple.Draw(brd);
	}
}

void Game::fillScreen(int r, int g, int b)
{
	for (int i = 0; i < gfx.ScreenWidth; i++)
		for (int j = 0; j < gfx.ScreenHeight; j++)
			gfx.PutPixel(i, j, r, g, b);
}
