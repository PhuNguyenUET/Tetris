#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "TitleScreen.cpp"

int main (int argc, char* args[]) {
    srand (time(0));
    SDL_Window* window = NULL;

    bool quit = false;
    bool playNext = false;

    double systemVolume = 1;
    double musicVolume = 1;
    int songIdx = 0;

    new TitleScreen(window, quit, systemVolume, musicVolume, songIdx);
    do {
        playNext = false;
        new Window(window, quit, playNext, systemVolume, musicVolume, songIdx);
    } while (!quit && playNext);
}