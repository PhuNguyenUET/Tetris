#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <queue>

#include "ScoreBoard.cpp"
#include "Pillar.cpp"

using std::string;
using std::cout;
using std::endl;
using std::to_string;
using std::queue;

class Window {
    private:
    SDL_Renderer* renderer;
    LTexture* background;
    LTexture* ground;
    SDL_Rect groundRect = {0, 0, SCREEN_WIDTH, GROUND};

    Bird* bird = NULL;
    ScoreBoard* scb = NULL;
    ScoreNoti* scnt = NULL;
    queue <Pillar*> pillars;
    Pillar* tmp_pillar;

    void init (SDL_Window* &window) {
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        int imgFlag = IMG_INIT_PNG;
        IMG_Init(imgFlag);
    }

    void loadMedia () {
        background = new LTexture(SCREEN_WIDTH, SCREEN_HEIGHT);
        (background)->loadFromFile("Graphics/background.png", renderer);
        ground = new LTexture(1200, GROUND);
        ground->loadFromFile("Graphics/Ground.png", renderer);
    } 

    void change () {
        background -> free();

        SDL_DestroyRenderer (renderer);
        renderer = NULL;

        IMG_Quit();
    }

    void close (SDL_Window* &window) {
        SDL_DestroyWindow (window);
        window = NULL;
        SDL_Quit();
    }

    public:
    Window (SDL_Window* &window, bool& playNext, bool& quit) {
        init(window);
        
        loadMedia();

        bird = new Bird(renderer);
        bird->setX(SCREEN_WIDTH/2 - bird->getWidth());
        bird->setY((SCREEN_HEIGHT - GROUND - bird->getHeight()) / 2);

        tmp_pillar = new Pillar (renderer);
        pillars.push(tmp_pillar);

        scb = new ScoreBoard();

        bool gameEnd = false;
        bool hitGround = false;
        bool hitPipe = false;
        bool gameStart = false;
        int prevScore = 0;
        int score = 0;
        double tmp = groundRect.x;
        SDL_Event e;

        scb->loadFromRenderedText(to_string(score), renderer);
        scb->render(SCREEN_WIDTH/2, 10, renderer);

        while (!quit && !hitGround) {
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    quit = true;
                } else {
                    if (!gameEnd) {
                        bird->handleEvent(e, gameStart);
                    }
                }
            }
            bird->move(gameEnd, hitGround, hitPipe, gameStart);

            if (gameStart) {
                Pillar* prev = pillars.back();
                if (prev -> getPosX() <= SCREEN_WIDTH - 220) {
                    tmp_pillar = new Pillar(renderer);
                    pillars.push(tmp_pillar);
                }

                if (pillars.front() -> getPosX() <= -tmp_pillar -> getWidth()) {
                    pillars.pop();
                } 
            }

            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderClear(renderer);

            background->render(0,0,renderer);
            ground->render(0, SCREEN_HEIGHT - GROUND, renderer, &groundRect);

            if (gameStart) {
                int n = pillars.size();
                for (int i = 0; i < n; i++) {
                    Pillar* pillar = pillars.front();

                    pillar->handleCollision(gameEnd, bird, hitPipe);
                    pillar -> updateScore(bird, score);
                    pillar->move(gameEnd);
                    pillar->render(renderer);

                    pillars.pop();
                    pillars.push(pillar);
                }
                ground -> render(0, SCREEN_HEIGHT - GROUND, renderer, &groundRect);
                if (!gameEnd) {
                    groundRect.x = tmp;
                    tmp += 0.0255;
                    if (tmp >= 1200 - SCREEN_HEIGHT) {
                        tmp = 0;
                    }
                }
            }

            bird->playAnimation(renderer);

            if (score != prevScore) {
                scb->loadFromRenderedText(to_string(score), renderer);
                prevScore = score;
            }

            if (gameStart) {
                scb->render((SCREEN_WIDTH - scb -> getWidth())/2,10,renderer);
            }

            SDL_RenderPresent(renderer);
        }
        
        if (quit) {
            change();
            close(window);
        }
        if (hitGround) {
            const int PLAYSPACE = SCREEN_HEIGHT - GROUND;
            scb->close();
            scnt = new ScoreNoti(renderer);
            scnt->loadFromRenderedText(to_string(score), renderer);
            //SDL_Event e;
            while (!quit && !playNext) {
                while (SDL_PollEvent(&e) != 0) {
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    } else {
                        scnt->handleEvent(e, playNext);
                    }
                }
                scnt -> render((SCREEN_WIDTH - scnt->getWidth()) / 2, (PLAYSPACE - scnt->getHeight()) / 2, renderer);
                SDL_RenderPresent(renderer);
            }

            if (quit) {
                change ();
                scnt->close();
                close (window);
            } else {
                scnt->close();
                change();
            }
        }

    }
};
