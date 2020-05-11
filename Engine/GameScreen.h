#pragma once
#include "MainWindow.h"
#include "GameScreen.h"
#include "Board.h"
#include "Snake.h"
#include "Fruit.h"
#include "Walls.h"
#include "FrameTimer.h"
#include "Sound.h"
#include "SpeedUp.h"
#include "Font.h"
#include "Button.h"


class GameScreen
{
public:
	GameScreen(Graphics& gfx);
	GameScreen() = default;
	//virtual ~GameScreen() = 0;
	virtual GameScreen* Update(MainWindow& wnd) = 0;
	virtual void Draw() = 0;
protected:
	Graphics& gfx;
};

class MenuScreen : public GameScreen
{
public:
	MenuScreen(Graphics& gfx);
	//~MenuScreen();
	GameScreen* Update(MainWindow& wnd);
	void Draw();
private:
	Font font;
	Button startButton;
};

class PlayingScreen : public GameScreen
{
public:
	PlayingScreen(Graphics& gfx);
	//~PlayingScreen();
	GameScreen* Update(MainWindow& wnd);
	void Draw();
private:
	void DrawScoreBar();
	void DrawScoreText();
private:
	FrameTimer ft;
	std::random_device rd;
	std::mt19937 rng;
	std::uniform_int_distribution<int> freqDist;

	Board brd;
	SpeedUp cucumber;

	float secondPerMove = 0.15f;
	float secondCount = 0.0f;
	Location delta_loc = { 1, 0 };
	Location prev_delta_loc = delta_loc;
	int score = 0;
	static constexpr int maxScore = 100;
	int prevScore = 0;
	float speedUpTimer = 0.0f;
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

	Font font;
};

class LosingScreen : public GameScreen
{
public:
	LosingScreen(Graphics& gfx);
	//~LosingScreen();
	GameScreen* Update(MainWindow& wnd);
	void Draw();
};

class WinningScreen : public GameScreen
{
public:
	WinningScreen(Graphics& gfx);
	//~WinningScreen();
	GameScreen* Update(MainWindow& wnd);
	void Draw();
};