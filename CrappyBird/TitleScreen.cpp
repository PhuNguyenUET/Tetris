#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <string>

// #include "LTexture.cpp"

const int SCREEN_WIDTH_B = 500;
const int SCREEN_HEIGHT_B = 750;

using std::string;
using std::cout;
using std::endl;
using std::to_string;

class TitleScreen {
    private:
        SDL_Renderer* renderer;

    public:
        void init (SDL_Window* &window) {
            SDL_Init (SDL_INIT_EVERYTHING);
            SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

            window = SDL_CreateWindow("Crappy Bird", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH_B, SCREEN_HEIGHT_B, SDL_WINDOW_SHOWN);
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

            SDL_SetRenderDrawColor (renderer, 0, 0, 0, 255);
            int imgFlag = IMG_INIT_PNG;
            IMG_Init(imgFlag);
        }

        void close () {
            SDL_DestroyRenderer(renderer);
            renderer = NULL;

            IMG_Quit();
        }

        TitleScreen (SDL_Window* &window) {
            init (window);
        }
};