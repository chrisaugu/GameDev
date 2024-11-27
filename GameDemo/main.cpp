//#include "Input.h"
#include "Game.h"
//#include "TGA.h"
//#include "Color.h";

int main(int argc, char** argv)
{
    Game game;
    bool success = game.Initialize();
    if (success) {
        game.RunLoop();
    }
    game.Shutdown();

    // init the window
    int width, height;

    //TGA tga;
    //Color* image = tga.load("image.tga", &width, &height);

    //if (image != NULL)
        //delete[] image;

    return EXIT_SUCCESS;
    //return 0;
}
