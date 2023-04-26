#ifndef LTEXTURE_H
#define LTEXTURE_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <string>

#include "Constants.h"

using std::string;
using std::cout;
using std::endl;
using std::to_string;

class LTexture {
    private:
        SDL_Texture* mTexture;

        int mWidth;
        int mHeight;
    public:
        int orgiWidth;
        int orgiHeight;

        LTexture(int width, int height);
        LTexture ();
        ~LTexture();
        void loadFromFile (string path, SDL_Renderer* &renderer);
        void free ();
        void render (int x, int y, SDL_Renderer* &renderer, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL);
        int getWidth ();
        int getHeight ();
        SDL_Texture* getTexture ();
};

#endif