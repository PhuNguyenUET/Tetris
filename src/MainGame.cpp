#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "../Header/Window.h"
#include "../Header/TitleScreen.h"

int main(int argc, char *args[])
{
    srand(time(0));
    SDL_Window *window = NULL;

    bool quit = false;
    bool playNext = false;
    bool turnBack = false;

    double systemVolume = 0.5;
    double musicVolume = 0.5;
    int songIdx = 0;

    // Create a window, then between titlescreen, game-screen and end-game screen
    // Destroy the texture rendering it and create a new one to fit the state
    new TitleScreen(window, quit, true, systemVolume, musicVolume, songIdx);
    do
    {
        if (turnBack)
        {
            new TitleScreen(window, quit, false, systemVolume, musicVolume, songIdx);
            turnBack = false;
        }
        playNext = false;
        new Window(window, quit, playNext, systemVolume, musicVolume, songIdx, turnBack);
    } while (!quit && (playNext || turnBack));
}