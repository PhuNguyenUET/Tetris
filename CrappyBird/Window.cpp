#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <string>

//#include "LTexture.cpp"
#include "Bird.cpp"

using std::string;
using std::cout;
using std::endl;
using std::to_string;

class Window {
    private:
    SDL_Renderer* renderer;
    SDL_Window* window;
    LTexture* background;

    Bird* bird = NULL;

    void init () {
        SDL_Init(SDL_INIT_EVERYTHING);
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

        window = SDL_CreateWindow("Crappy Bird", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        int imgFlag = IMG_INIT_PNG;
        IMG_Init(imgFlag);
    }

    void loadMedia () {
        background = new LTexture(SCREEN_WIDTH, SCREEN_HEIGHT);
        (background)->loadFromFile("Graphics/BackGround.png", renderer);
    } 

    void close () {
        background -> free();

        SDL_DestroyRenderer (renderer);
        SDL_DestroyWindow (window);
        window = NULL;
        renderer = NULL;

        IMG_Quit();
        SDL_Quit();
    }

    public:
    Window () {
        init();
        
        loadMedia();

        bird = new Bird(renderer);
        bird->setX(20);
        bird->setY((SCREEN_HEIGHT - GROUND - bird->getHeight()) / 2);

        bool quit = false;
        SDL_Event e;

        while (!quit) {
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    quit = true;
                } else {
                    bird->handleEvent(e);
                }
            }
            bird->move();

            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderClear(renderer);

            background->render(0,0,renderer);

            bird->render(renderer);

            SDL_RenderPresent(renderer);
        }

        close();
    }
};
