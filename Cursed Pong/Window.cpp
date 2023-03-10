#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <chrono>

#include "Paddle.cpp"

using std::string;
using std::cout;
using std::endl;

class Window {
    SDL_Window* window;
    SDL_Renderer* renderer;
    Paddle* player1;
    Paddle* player2;
    Ball* ball; 

    void init () {
        SDL_Init(SDL_INIT_EVERYTHING);
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

        window = SDL_CreateWindow("Cursed Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

        SDL_SetRenderDrawColor (renderer, 0, 0, 0, 255);

        int imgFlag = IMG_INIT_PNG;
        IMG_Init(imgFlag); 
    }   

    void close () {
        SDL_DestroyRenderer(renderer);
        renderer = NULL;

        SDL_DestroyWindow(window);
        window = NULL;

        IMG_Quit();
        SDL_Quit();
    }

    public: 
    Window () {
        init ();

        player1 = new Paddle(0);
        player2 = new Paddle(SCREEN_WIDTH - (*player2).PWIDTH);
        ball = new Ball();
        bool quit = false;
        bool inGame = true;
        int timeMark = 0;
        SDL_Event e;

        while (!quit) {
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    quit = true;
                } else {
                    player1->handleEvent(e);
                }
            }

            player1->move();
            ball->move(player1 -> getCollider(), player2 -> getCollider());
            if (inGame == true) {
                player2->selfMove(player2->getCollider(), ball);
            }

            SDL_SetRenderDrawColor (renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

            SDL_SetRenderDrawColor (renderer, 255, 255, 255, 255);
            for (int i = 0; i <= SCREEN_HEIGHT; i+= 30) {
                SDL_RenderDrawLine(renderer, SCREEN_WIDTH/2, i, SCREEN_WIDTH/2, i + 15);
            }
            SDL_SetRenderDrawColor (renderer, 0, 0, 0, 255);

            player1->render(renderer);
            player2->render(renderer);
            ball->render(renderer);

            SDL_RenderPresent(renderer);

            if (inGame == true && !ball->isBallInGame()) {
                timeMark = SDL_GetTicks();
                inGame = false;
                player2 -> forceStop();
            }

            if ((inGame == false) && (SDL_GetTicks() - timeMark > 1000)) {
                ball = new Ball();
                inGame = true;
            }
        }
    }

};