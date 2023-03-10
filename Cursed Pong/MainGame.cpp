#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include "Window.cpp"
#include "TitleScreen.cpp"

using std::string;
using std::cout;
using std::endl;

int main (int argc, char* args[]) {
    SDL_Window* window;
    srand(time(0));
    new TitleScreen();
    new Window();
}