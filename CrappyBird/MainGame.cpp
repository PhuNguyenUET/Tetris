#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include "Window.cpp"
#include "TitleScreen.cpp"

using std::string;
using std::cout;
using std::endl;
using std::to_string;

int main (int argc, char* args[]) {
    srand(time(0));

    SDL_Window* window;
    bool playNext = false;

    TitleScreen* ttsc = new TitleScreen(window);
    ttsc->close();

    do {
        playNext = false;
        new Window(window, playNext);
    } while (playNext);
}