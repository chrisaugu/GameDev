#ifndef GAME_H
#define GAME_H

#pragma once
// for initializing and shutdown functions
#include <SDL2/SDL.h>
#include "Player.h"
#include <unordered_map>
#include <string>
#include <vector>


// Vector2 struct just stores x/y coordinates
// (for now)
struct Vector2
{
	float x;
	float y;
};

struct Ball
{
    float x;
    float y;
    float vX;
    float vY;
};

class Game
{
public:
        Game();

        // initialize the game
        bool Initialize();

        // runs the game loop till the game is over
        void RunLoop();

        // shutdown the game
        void Shutdown();

private:
    // helper functions for the game loop
    void ProcessInput();

    void UpdateGame();

    void GenerateOutput();

    // Window created by SDL
    SDL_Window* mWindow;

    // Game should continue to run
    bool mIsRunning;

    // Renderer
    SDL_Renderer* mRenderer;

    // The surface contained by the window
    SDL_Surface* mScreenSurface;

	// Pong specific
	// Direction of left paddle
	int mLeftPaddleDir;
	// Direction of right paddle
	int mRightPaddleDir;
	// Position of paddle
	Vector2 mLeftPaddlePos;
	// Position of right paddle
	Vector2 mRightPaddlePos;
	// Position of ball
	Vector2 mBallPos;
	// Velocity of ball
	Vector2 mBallVel;

    // balls
	std::vector<Vector2> mBalls;
	std::vector<Ball> balls;

    Player* mPlayer;

    Uint32 mTicksCount;

protected:
};

#endif GAME_H
