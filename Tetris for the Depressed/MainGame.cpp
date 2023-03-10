#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "Window.cpp"

int main (int argc, char* args[]) {
    srand (time(0));
    new Window();
}