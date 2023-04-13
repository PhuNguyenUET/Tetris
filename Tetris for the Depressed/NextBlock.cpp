#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "LTexture.cpp"

class nextBlock
{
private:
    const int neonEdge = 230;

public:
    LTexture *neon = new LTexture(neonEdge, neonEdge);
};