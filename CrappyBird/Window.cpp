#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <queue>

//#include "LTexture.cpp"
#include "Pillar.cpp"

using std::string;
using std::cout;
using std::endl;
using std::to_string;
using std::queue;

class Window {
    private:
    SDL_Renderer* renderer;
    SDL_Window* window;
    LTexture* background;

    Bird* bird = NULL;
    queue <Pillar*> pillars;
    Pillar* tmp_pillar;

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
        bird->setX(SCREEN_WIDTH/2 - bird->getWidth());
        bird->setY((SCREEN_HEIGHT - GROUND - bird->getHeight()) / 2);

        tmp_pillar = new Pillar (renderer);
        pillars.push(tmp_pillar);

        bool quit = false;
        bool gameEnd = false;
        SDL_Event e;

        while (!quit) {
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    quit = true;
                } else {
                    if (!gameEnd) {
                        bird->handleEvent(e);
                    }
                }
            }
            bird->move();

            Pillar* prev = pillars.back();
            if (prev -> getPosX() <= SCREEN_WIDTH - 220) {
                tmp_pillar = new Pillar(renderer);
                pillars.push(tmp_pillar);
            }

            if (pillars.front() -> getPosX() <= -tmp_pillar -> getWidth()) {
                pillars.pop();
            } 

            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderClear(renderer);

            background->render(0,0,renderer);

            int n = pillars.size();
            for (int i = 0; i < n; i++) {
                Pillar* pillar = pillars.front();

                pillar->handleCollision(gameEnd, bird);
                pillar->move(gameEnd);
                pillar->render(renderer);

                pillars.pop();
                pillars.push(pillar);
            }

            bird->render(renderer);


            SDL_RenderPresent(renderer);
        }

        close();
    }
};
