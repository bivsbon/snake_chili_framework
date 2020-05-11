#pragma once
#include "MainWindow.h"

class GameState
{
	virtual ~GameState() {};
	virtual void HandleInput(MainWindow& wnd);
	virtual void Update();
};

class MenuState : public GameState
{
	virtual void HandleInput(MainWindow& wnd)
	{
		if (start.mouseHoverOn(wnd.mouse.GetPos()))
		{
			if (wnd.mouse.LeftIsPressed())
			{
				state = State::GAME;
			}
		}
	}
};