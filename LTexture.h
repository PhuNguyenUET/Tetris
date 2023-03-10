#ifndef LTEXTURE_H
#define LTEXTURE_H

#include <iostream>
#include <cstdlib>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class LTexture {
    private:
        SDL_Texture* mTexture;
        int mWidth;
        int mHeight;
    public:
        LTexture();
        ~LTexture();
        bool loadFromFile(std::string path, SDL_Renderer* renderer);
        void free ();
        void render (int x, int y, SDL_Renderer* renderer);
        int getWidth();
        int getHeight();
};

#endif