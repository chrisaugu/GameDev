//#include <SDL2/SDL.h>
//#include <SDL2/SDL_Image.h>
//#include <SDL2/SDL_Timer.h>

#include "Game.h"

const int thickness = 15;
const float paddleH = 100.0f;

// Game constructor
Game::Game(): mWindow(nullptr), mRenderer(nullptr), mTicksCount(0), mIsRunning(true), mPaddleDir(0), mPlayer(nullptr)
{

}

bool Game::Initialize()
{
    int sdlResult = SDL_Init(SDL_INIT_VIDEO);
    //SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);

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
        800, // Width of window
        600, // Height of window
        0 // Flags (0 for no flags set)
    );
     // "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN

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
	mPaddlePos.x = 10.0f;
	mPaddlePos.y = 600.0f/2.0f;
	mBallPos.x = 800.0f/2.0f;
	mBallPos.y = 600.0f/2.0f;
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

    mPaddleDir = 0;
    if (state[SDL_SCANCODE_W]) {
        mPaddleDir = -1;
    }

    if (state[SDL_SCANCODE_S]) {
        mPaddleDir = 1;
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

    // Update all actors
    mUpdatingActors = true;
    for (auto actor : mActors)
    {
        actor->Update(deltaTime);
    }
    mUpdatingActors = false;
    // Move any pending actors to mActors
    for (auto pending : mPendingActors)
    {
        mActors.emplace_back(pending);
    }
    mPendingActors.clear();
    // Add any dead actors to a temp vector
    std::vector<Actor*> deadActors;

    for (auto actor : mActors)
    {
        if (actor->GetState() == Actor::EDead)
        {
            deadActors.emplace_back(actor);
        }
    }

    // Delete dead actors (which removes them from mActors)
    for (auto actor : deadActors)
    {
        delete actor;
    }

    if (mPaddleDir != 0)
    {
        mPaddlePos.y += mPaddleDir * 300.0f * deltaTime;

        // make sure the paddle does not move off screen!
        if (mPaddlePos.y < (paddleH/2.0f * thickness))
        {
            mPaddlePos.y = (paddleH/2.0f * thickness);
        }
        else if (mPaddlePos.y > (600.0f - paddleH/2.0f - thickness))
        {
            mPaddlePos.y = (600.0f - paddleH/2.0f - thickness);
        }
    }

    // mBallVel(-200.0f, 235.0f);
    mBallPos.x += mBallVel.x * deltaTime;
    mBallPos.y += mBallVel.y * deltaTime;

    // Bounce if needed
	// Did we intersect with the paddle?
	float diff = mPaddlePos.y - mBallPos.y;

	// Take absolute value of difference
	diff = (diff > 0.0f) ? diff : -diff;
	if (
		// Our y-difference is small enough
		diff <= paddleH / 2.0f &&
		// We are in the correct x-position
		mBallPos.x <= 25.0f && mBallPos.x >= 20.0f &&
		// The ball is moving to the left
		mBallVel.x < 0.0f)
	{
		mBallVel.x *= -1.0f;
	}
	// Did the ball go off the screen? (if so, end game)
	//else if (mBallPos.x <= 0.0f)
	//{
		//mIsRunning = false;
	//}
	// did the ball collide with the left wall?
	else if (mBallPos.x <= thickness && mBallVel.x < 0.0f) {
		mBallVel.x *= -1.0f;
	}
	// Did the ball collide with the right wall?
	else if (mBallPos.x >= (800.0f - thickness) && mBallVel.x > 0.0f)
	{
		mBallVel.x *= -1.0f;
	}

	// Did the ball collide with the top wall?
	if (mBallPos.y <= thickness && mBallVel.y < 0.0f)
	{
		mBallVel.y *= -1;
	}
	// Did the ball collide with the bottom wall?
	else if (mBallPos.y >= (600 - thickness) && mBallVel.y > 0.0f)
	{
		mBallVel.y *= -1;
	}

	// TODO: remove right wall and implement right paddle
	if (mBallPos.x <= 0 && mBallVel.x > 0.0f) {
        mBallVel.x *= -1;
	}
}

void Game::GenerateOutput()
{
    SDL_SetRenderDrawColor(
       mRenderer,
       0, // R
       0, // G
       255, // B
       255 // A
    );
    // clear back buffer
    SDL_RenderClear(mRenderer);

    // draw walls
    SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);

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

	// Draw right wall
	wall.x = 800 - thickness;
	wall.y = 0;
	wall.w = thickness;
	wall.h = 800;
	SDL_RenderFillRect(mRenderer, &wall);

	// Draw left wall
	wall.x = 0;
	wall.y = 0;
	wall.w = thickness;
	wall.h = 600;
	SDL_RenderFillRect(mRenderer, &wall);

	// Draw paddle
	SDL_Rect paddle {
		static_cast<int>(mPaddlePos.x),
		static_cast<int>(mPaddlePos.y - paddleH/2),
		thickness,
		static_cast<int>(paddleH)
	};
	SDL_RenderFillRect(mRenderer, &paddle);

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

    // Because ~Actor calls RemoveActor, use a different style loop
    while (!mActors.empty())
    {
        delete mActors.back();
    }
}

void Game::AddActor(Actor* actor)
{
    // If updating actors, need to add to pending
    if (mUpdatingActors)
    {
        mPendingActors.emplace_back(actor);
    }
    else
    {
        mActors.emplace_back(actor);
    }
}

void Game::loadImage() {
    SDL_Texture* LoadTexture(const char* fileName)
    {
        // Load from file
        SDL_Surface* surf = IMG_Load(fileName);
        if (!surf)
        {
            SDL_Log("Failed to load texture file %s", fileName);
            return nullptr;
        }
        // Create texture from surface
        SDL_Texture* text = SDL_CreateTextureFromSurface(mRenderer, surf);
        SDL_FreeSurface(surf);

        if (!text)
        {
            SDL_Log("Failed to convert surface to texture for %s", fileName);
            return nullptr;
        }

        return text;
    }
}

void Game::AddSprite(SpriteComponent* sprite)
{
    // Find the insertion point in the sorted vector
    // (The first element with a higher draw order than me)
    int myDrawOrder = sprite->GetDrawOrder();
    auto iter = mSprites.begin();

    for ( ; iter != mSprites.end(); ++iter)
    {
        if (myDrawOrder < (*iter)->GetDrawOrder())
        {
            break;
        }
    }
    // Inserts element before position of iterator
    mSprites.insert(iter, sprite);
}
