#ifndef NEXTBLOCK_H
#define NEXTBLOCK_H

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "LTexture.h"

using std::vector;

class NextBlock {
private:
    const int neonEdge = 230;

public:
    LTexture *neon = new LTexture(neonEdge, neonEdge);
    int nextShape[4][2];
    LTexture* tiles;
    SDL_Rect indTile[8];

    void loadMedia (SDL_Renderer* renderer);
    void render (int x, int y, SDL_Renderer* renderer, vector <SDL_Point> nextShapeArr, int nxtColorIdx);
};

#endif