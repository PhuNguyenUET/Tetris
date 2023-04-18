#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

class ProgressBar {
    private:
        int xPos;
        int yPos;
        int pointerPos;
        LTexture* bar;
        double volume;
        LTexture* circle;
        int circlePosX = barWidth + barPos.x;
    public:
        SDL_Point barPos;
        const int barWidth = 350;
        const int barHeight = 20;
        ProgressBar (SDL_Renderer* &renderer, int x, int y, double& volume);
        void render (SDL_Renderer* &renderer);
        void handleEvent (SDL_Event e, double& volume);
};

#endif