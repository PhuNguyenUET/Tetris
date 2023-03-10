#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include "Window.cpp"

using std::string;
using std::cout;
using std::endl;

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 700;

int main (int argc, char* args[]) {
    new Window();
}