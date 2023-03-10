#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <string>

#include "LTexture.cpp";

using std::string;
using std::cout;
using std::endl;
using std::to_string;

class Pillar {
    private:
    const int OPEN_WIDTH = 30;
    const int PLAYSPACE = SCREEN_HEIGHT - GROUND;
    const int OPEN_HEIGHT = 50;
    const int HORI_VEL = 0.1;

    int openY;
    int vel;

    SDL_Rect upCollider;
    SDL_Rect downCollider;

    LTexture* upPillar = NULL;
    LTexture* downPillar = NULL;
    
    public:

    Pillar () {
        openY = rand() % (PLAYSPACE - 150) + 100;
    }
};