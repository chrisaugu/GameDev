//#include <SDL2/SDL.h>
//#include <SDL2/SDL_Image.h>
//#include <SDL2/SDL_Timer.h>
#include <iostream>
#include <stdio.h>

#include "Game.h"
#include "Player.h"
#include "vector"
#include "string.h"

const int thickness = 15;
const float paddleH = 100.0f;
const float winHeight = 600.0f;
const float winWidth = 800.0f;

// Game constructor
Game::Game(): mWindow(nullptr),
              mRenderer(nullptr),
              mTicksCount(0),
              mIsRunning(true),
              mLeftPaddleDir(0),
              mRightPaddleDir(0),
              mPlayer(nullptr),
              mBalls(10)
{
}

bool Game::Initialize()
{
    int sdlResult = SDL_Init(SDL_INIT_VIDEO);
    // SDL_Init(SDL_INIT_EVERYTHING);

    // returns zero on success else non-zero
    if (sdlResult != 0)
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }

    mWindow = SDL_CreateWindow(
       "Game Demo", // Window title
        SDL_WINDOWPOS_CENTERED, // Top left x-coordinate of window
        SDL_WINDOWPOS_CENTERED, // Top left y-coordinate of window
        winWidth, // Width of window
        winHeight, // Height of window
        0 // Flags (0 for no flags set)
    );

	if (!mWindow)
    {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }

    SDL_Surface* icon = SDL_LoadBMP("Assets/Images/z.bmp");
    //SDL_WM_SetIcon(icon, NULL);
    SDL_SetWindowIcon(mWindow, icon);

    mRenderer = SDL_CreateRenderer(
        mWindow, // Window to create renderer for
        -1, // Usually -1
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (!mRenderer)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}

	//
	mLeftPaddlePos.x = 10.0f;
	mLeftPaddlePos.y = winHeight/2.0f;
	mRightPaddlePos.x = 60.0f;
	mRightPaddlePos.y = winHeight/2.0f;
	mBallPos.x = winWidth/2.0f;
	mBallPos.y = winHeight/2.0f;
	mBallVel.x = -200.0f;
	mBallVel.y = 235.0f;

	return true;
}

void Game::RunLoop()
{
    while(mIsRunning)
    {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

void Game::ProcessInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            // If this is an SDL_QUIT event, end loop
            case SDL_QUIT:
                mIsRunning = false;
                break;
        }
    }

    // Get state of keyboard
    const Uint8* state = SDL_GetKeyboardState(NULL);

    // If escape is pressed, also end loop
    if (state[SDL_SCANCODE_ESCAPE]) {
        mIsRunning = false;
    }

    // Update left paddle direction based on W/S keys
	mLeftPaddleDir = 0;
    if (state[SDL_SCANCODE_W]) {
        mLeftPaddleDir = -1;
    }
    if (state[SDL_SCANCODE_S]) {
        mLeftPaddleDir = 1;
    }

    // Update right paddle direction based on I/K keys
    mRightPaddleDir = 0;
    if (state[SDL_SCANCODE_I]) {
        mRightPaddleDir = -1;
    }
    if (state[SDL_SCANCODE_K]) {
        mRightPaddleDir = 1;
    }
}

void Game::UpdateGame() {
    // Wait until 16ms has elapsed since last frame
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));

    // Delta time is the difference in ticks from last frame
    // (converted to seconds)
    float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;

    // Clamp maximum delta time value
    if (deltaTime > 0.05f)
    {
        deltaTime = 0.05f;
    }

    mTicksCount = SDL_GetTicks();

    mPlayer = new Player();
    delete mPlayer;
    //enemy.mPosition.x += 5;

    if (mLeftPaddleDir != 0)
    {
        mLeftPaddlePos.y += mLeftPaddleDir * 300.0f * deltaTime;

        // make sure the paddle does not move off screen!
        if (mLeftPaddlePos.y < (paddleH/2.0f + thickness))
        {
            mLeftPaddlePos.y = (paddleH/2.0f + thickness);
        }
        else if (mLeftPaddlePos.y > (winHeight - paddleH/2.0f - thickness))
        {
            mLeftPaddlePos.y = (winHeight - paddleH/2.0f - thickness);
        }
    }

    // right paddle checks
    if (mRightPaddleDir != 0)
    {
        mRightPaddlePos.y += mRightPaddleDir * 300.0f * deltaTime;

        // make sure the right paddle does not move offscreen
        if (mRightPaddlePos.y < (paddleH/2.0f + thickness))
        {
            mRightPaddlePos.y = (paddleH/2.0f + thickness);
        }
        else if (mRightPaddlePos.y > (winHeight - paddleH/2.0f - thickness))
        {
            mRightPaddlePos.y = (winHeight - paddleH/2.0f - thickness);
        }
    }

    mBallPos.x += mBallVel.x * deltaTime;
    mBallPos.y += mBallVel.y * deltaTime;

    // Bounce if needed
	// Did we intersect with the left paddle?
	float diff = mLeftPaddlePos.y - mBallPos.y;

	// Take absolute value of difference
	diff = (diff > 0.0f) ? diff : -diff;
	if (
		// Our y-difference is small enough
		diff <= paddleH / 2.0f &&
		// We are in the correct x-position
		mBallPos.x <= 25.0f && mBallPos.x >= 20.0f &&
		// The ball is moving to the left
		mBallVel.x < 0.0f
    )
	{
		mBallVel.x *= -1.0f;
	}
	// Did the ball go off the screen? (if so, end game)
	else if (mBallPos.x <= 0.0f)
	{
		mIsRunning = false;
	}

	// TODO: remove right wall and implement right paddle
	// Bounce if needed
	// Did we intersect with the right paddle?
	float rightDiff = mRightPaddlePos.y - mBallPos.y;

	// Take absolute value of difference
	rightDiff = (rightDiff > 0.0f) ? rightDiff : -rightDiff;

	if (
		// Our y-difference is small enough
		rightDiff <= paddleH / 2.0f &&
		// We are in the correct x-position
		mBallPos.x <= 785.0f && mBallPos.x >= 777.5f &&
		// The ball is moving to the right
		mBallVel.x > 0.0f
    )
	{
		mBallVel.x *= -1.0f;
	}
	// Did the ball go off the screen? (if so, end game)
	else if (mBallPos.x >= winWidth)
	{
        mIsRunning = false;
	}

	// Did the ball collide with the top wall?
	if (mBallPos.y <= 0 && mBallVel.y < 0.0f)
	{
		mBallVel.y *= -1;
	}
	// Did the ball collide with the bottom wall?
	else if (mBallPos.y >= (winHeight - 0) && mBallVel.y > 0.0f)
	{
		mBallVel.y *= -1;
	}
}

void Game::GenerateOutput()
{
    SDL_SetRenderDrawColor(
       mRenderer,
       0, // R
       0, // G
       0, // B
       255 // A
    );
    // clear back buffer
    SDL_RenderClear(mRenderer);

    // draw walls
    SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);

    /**
    SDL_Rect wall {
        0, // Top left x
        0, // Top left y
        800, // Width
        thickness // Height
    };
    SDL_RenderFillRect(mRenderer, &wall);

    // Draw bottom wall
	wall.y = 600 - thickness;
	SDL_RenderFillRect(mRenderer, &wall);
    */

	// Draw left paddle
	SDL_Rect paddleLeft {
		static_cast<int>(thickness/2),
		static_cast<int>(mLeftPaddlePos.y - paddleH/2),
		thickness,
		static_cast<int>(paddleH)
	};
	SDL_RenderFillRect(mRenderer, &paddleLeft);

	// Draw right paddle
	SDL_Rect paddleRight {
		static_cast<int>(winWidth - thickness*1.5),
		static_cast<int>(mRightPaddlePos.y - paddleH/2),
		thickness,
		static_cast<int>(paddleH)
	};
	SDL_RenderFillRect(mRenderer, &paddleRight);

	// Draw ball
	SDL_Rect ball {
		static_cast<int>(mBallPos.x - thickness/2),
		static_cast<int>(mBallPos.y - thickness/2),
		thickness,
		thickness
	};
	SDL_RenderFillRect(mRenderer, &ball);

    // swap colors from front buffer and
    SDL_RenderPresent(mRenderer);
}

enum Lights {
    Red,
    Blue,
    Green
};

void Game::Shutdown()
{
    SDL_DestroyWindow(mWindow);
    SDL_DestroyRenderer(mRenderer);
    SDL_Quit();
}

