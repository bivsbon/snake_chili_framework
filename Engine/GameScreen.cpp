#include "GameScreen.h"

GameScreen::GameScreen(Graphics& gfx)
	:
	gfx(gfx)
{}

MenuScreen::MenuScreen(Graphics& gfx)
	:
	GameScreen(gfx),
	font("Fonts\\Consolas13x24.bmp", Colors::White),
	startButton({ 300, 225 }, 200, 150, font, "START")
{}

GameScreen* MenuScreen::Update(MainWindow& wnd)
{
	if (startButton.mouseHoverOn(wnd.mouse.GetPos()))
	{
		if (wnd.mouse.LeftIsPressed())
		{
			return new PlayingScreen(gfx);
		}
	}
	return this;
}

void MenuScreen::Draw()
{
	gfx.FillScreen(200, 200, 200);
	startButton.Draw(gfx);
}

PlayingScreen::PlayingScreen(Graphics& gfx)
	:
	GameScreen(gfx),
	brd(gfx),
	rng(rd()),
	freqDist(20, 30),
	background(L"Sounds\\soundtrack.wav"),
	nom(L"Sounds\\nom.wav"),
	speedup(L"Sounds\\aaah.wav"),
	font("Fonts\\Consolas13x24.bmp", Colors::White)
{
	background.Play();
}

GameScreen* PlayingScreen::Update(MainWindow& wnd)
{
	const float dt = ft.Mark();
	if (!speedingUp)
	{
		// Keyboard input
		if (wnd.kbd.KeyIsPressed(VK_UP))
			delta_loc = { 0, -1 };
		if (wnd.kbd.KeyIsPressed(VK_DOWN))
			delta_loc = { 0,  1 };
		if (wnd.kbd.KeyIsPressed(VK_LEFT))
			delta_loc = { -1,  0 };
		if (wnd.kbd.KeyIsPressed(VK_RIGHT))
			delta_loc = { 1,  0 };
		if (wnd.kbd.KeyIsPressed(VK_RETURN))
			speedingUp = !speedingUp;

		// Adjust the frame rate
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
				if (++score == maxScore)
				{
					background.StopAll();
					//speedup.StopAll();
					return new WinningScreen(gfx);
				}
				if (!speedUpMode)
				{
					nom.Play(); // Eating sound
				}
				brd.SnakeGrow();
				// Spawn a wall at random place every 2 apples eaten
				if (score % 2 == 0)
				{
					brd.SpawnNewWall();
				}
				// Keep repawning apple if it spawns on snake or walls
				brd.SpawnNewFruit();
			}

			// Gameover scenarios
			if (brd.SnakeEatsWalls(delta_loc) || brd.SnakeIsOutside(delta_loc) || brd.SnakeEatsItself(delta_loc))
			{
				background.StopAll();
				speedup.StopAll();
				return new LosingScreen(gfx);
			}

			// Eating cucumber
			if (brd.SnakeEatSpeedUp(delta_loc))
			{
				brd.TerminateCucumber();
				secondPerMove = 0.07f;
				speedUpTimer = 0.0f;
				speedUpMode = true;
				speedingUp = true;
				background.StopAll();
				speedup.StopOne();
				speedup.Play();
			}
			brd.SnakeMoveBy(delta_loc);
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
	}
	else
	{
		pauseCounter += dt;
		if (pauseCounter >= pauseDuration)
		{
			pauseCounter = 0.0f;
			speedingUp = false;
		}
	}

	return this;
}

void PlayingScreen::Draw()
{
	gfx.FillScreen(200, 200, 200);
	brd.Draw(gfx);
	DrawScoreBar();
	DrawScoreText();
}

void PlayingScreen::DrawScoreBar()
{
	float percentage = (float)score / (float)maxScore;
	float w = percentage * 760.0f;
	// Score progress
	gfx.drawRectDim(20, 20, (int)w, 30, Colors::Magenta, true);
	//Border
	gfx.drawRectDim(19, 19, 762, 32, Colors::Black, false);
	gfx.drawRectDim(18, 18, 764, 34, Colors::Black, false);
	gfx.drawRectDim(17, 17, 766, 36, Colors::Black, false);
}

void PlayingScreen::DrawScoreText()
{
	std::string scoreText = std::to_string(score);
	std::string maxScoreText = std::to_string(maxScore);
	const int l = (int)scoreText.length() + (int)maxScoreText.length() + 1;
	const int total = l * font.getGlyphWidth();

	const int posX = (Graphics::ScreenWidth - total) / 2;
	font.MyDrawText(scoreText + "/" + maxScoreText, { posX, 23 }, Colors::Black, gfx);
}

LosingScreen::LosingScreen(Graphics& gfx)
	:
	GameScreen(gfx),
	dead(L"Sounds\\oof.wav"),
	font("Fonts\\Consolas13x24.bmp", Colors::White),
	tryAgainButton({ 300, 225 }, 200, 150, font, "TRY AGAIN")
{
	dead.Play();
}

GameScreen* LosingScreen::Update(MainWindow& wnd)
{
	if (wnd.kbd.KeyIsPressed(VK_ESCAPE))
	{
		return new MenuScreen(gfx);
	}
	if (tryAgainButton.mouseHoverOn(wnd.mouse.GetPos()))
	{
		if (wnd.mouse.LeftIsPressed())
		{
			return new PlayingScreen(gfx);
		}
	}

	return this;
}

void LosingScreen::Draw()
{
	gfx.FillScreen(255, 0, 0);
	tryAgainButton.Draw(gfx);
}

WinningScreen::WinningScreen(Graphics& gfx)
	:
	GameScreen(gfx)
{}

GameScreen* WinningScreen::Update(MainWindow & wnd)
{
	if (wnd.kbd.KeyIsPressed(VK_ESCAPE))
	{
		return new MenuScreen(gfx);
	}
	return this;
}

void WinningScreen::Draw()
{
	gfx.FillScreen(0, 255, 0);
}