#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "LTexture.h"

class ProgressBar
{
private:
    const int barWidth = 350;
    const int barHeight = 20;

    int pointerPos;
    LTexture *bar;
    double volume;
    LTexture *circle;
    SDL_Point barPos = {0, 0};
    int circlePosX = barWidth + barPos.x;

public:
    ProgressBar(SDL_Renderer *&renderer, int x, int y, double &volume);
    void render(SDL_Renderer *&renderer);
    void handleEvent(SDL_Event e, double &volume);
};

#endif