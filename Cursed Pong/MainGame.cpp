#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include "Window.cpp"
#include "TitleScreen.cpp"
#include "ResultScreen.cpp"

using std::string;
using std::cout;
using std::endl;

int main (int argc, char* args[]) {
    SDL_Window* window;
    bool shutDown = false;
    bool win = false;
    bool con = true;

    srand(time(0));
    new TitleScreen(window, shutDown);
    if (!shutDown) {
        while (con && !shutDown) {
            new Window(window, shutDown, win);
            if (!shutDown) {
                new ResultScreen(window, win, con);
            }
        }
    }
}