#ifndef BUTTON_H
#define BUTTON_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <string>

using std::string;
using std::cout;
using std::endl;
using std::to_string;

class Button {
    private:
        SDL_Texture* buttonTexture;
        SDL_Point pos;
        int width;
        int height;
    public:
        Button (SDL_Renderer* &renderer, string path, int width, int height);
        void setPos (int x, int y);
        void handleEvent (SDL_Event& e, bool& change);
        void render (SDL_Renderer* &renderer);
        void close ();
};

#endif