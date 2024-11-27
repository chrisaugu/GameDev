#ifndef GAME_H
#define GAME_H

// for initializing and shutdown functions
#include <SDL2/SDL.h>
#include "Player.h"

// Vector2 struct just stores x/y coordinates
// (for now)
struct Vector2
{
	float x;
	float y;
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

        // add actor
        void AddActor(Actor* actor);

        // load image
        void loadImage();

        // add Sprite
        void AddSprite(SpriteComponent* sprite);

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
	// Direction of paddle
	int mPaddleDir;
	// Position of paddle
	Vector2 mPaddlePos;
	// Position of ball
	Vector2 mBallPos;
	// Velocity of ball
	Vector2 mBallVel;

    // balls
	//std::vector<Ball> mBalls;
	// actors
	std::vector<Actor> mActors;
    // sprites
	std::vector<SpriteComponent> mSprites;

    Player* mPlayer;

    Uint32 mTicksCount;

protected:
};

#endif GAME_H
