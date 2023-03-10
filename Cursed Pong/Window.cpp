#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <chrono>
#include <string>
#include <bitset>

#include "Paddle.cpp"
#include "ScoreBoard.cpp"

using std::string;
using std::cout;
using std::endl;
using std::to_string;

class Window {
    Mix_Music *music = NULL;
    Mix_Chunk* referee = NULL;
    SDL_Renderer* renderer;
    Paddle* player1;
    Paddle* player2;
    Ball* ball; 
    ScoreBoard* scorePlayer1;
    ScoreBoard* scorePlayer2; 

    int score1prev = 0;
    int score2prev = 0;
    int score1 = 0;
    int score2 = 0;
    string score1s;
    string score2s;

    void init (SDL_Window* &window) {
        SDL_Init(SDL_INIT_EVERYTHING);
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

        SDL_SetRenderDrawColor (renderer, 0, 0, 0, 255);

        int imgFlag = IMG_INIT_PNG;
        IMG_Init(imgFlag); 

        Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

        music = Mix_LoadMUS("Audio/Mario.wav");
        Mix_PlayMusic(music, -1);

        referee = Mix_LoadWAV("Audio/Referee.wav");

        TTF_Init();
    }   

    void close (SDL_Window* &window) {
        SDL_DestroyWindow(window);
        window = NULL;
    }

    void change () {
        Mix_FreeMusic(music);
        music = NULL;

        Mix_FreeChunk(referee);
        referee = NULL;

        SDL_DestroyRenderer(renderer);
        renderer = NULL;

        IMG_Quit();
        Mix_Quit();
        TTF_Quit();
    }

    public: 
    Window (SDL_Window* &window, bool& shutDown, bool& win) {
        init (window);

        player1 = new Paddle(0);
        player2 = new Paddle(SCREEN_WIDTH - (*player2).PWIDTH);
        ball = new Ball();
        scorePlayer1 = new ScoreBoard();
        scorePlayer2 = new ScoreBoard();
        bool quit = false;
        bool inGame = true;
        int timeMark = 0;
        SDL_Event e;

        scorePlayer1->loadFromRenderedText("0", renderer);
        scorePlayer2->loadFromRenderedText("0", renderer);

        while (!quit && !shutDown) {
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    shutDown = true;
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
            if ((score1 != score1prev) || (score2 != score2prev)) {
                if (score1 >= 10 && scorePlayer1->getWidth() != 80) {
                    scorePlayer1->setWidth(80);
                }
                if (score2 >= 10 && scorePlayer2->getWidth() != 80) {
                    scorePlayer2->setWidth(80);
                }
                score1prev = score1;
                score2prev = score2;
                score1s = to_string(score1);
                score2s = to_string(score2);
                scorePlayer1->loadFromRenderedText(score1s, renderer);
                scorePlayer2->loadFromRenderedText(score2s, renderer);
            }
            scorePlayer1->render(300, 20, renderer);
            scorePlayer2->render(460, 20, renderer);
            player1->render(renderer);
            player2->render(renderer);
            ball->render(renderer);

            SDL_RenderPresent(renderer);

            if (inGame == true && !ball->isBallInGame(score1, score2)) {
                Mix_PlayChannel(-1, referee, 0);
                timeMark = SDL_GetTicks();
                inGame = false;
                player2 -> forceStop();
            }

            if ((inGame == false) && (SDL_GetTicks() - timeMark > 1000)) {
                ball->close();
                ball = new Ball();
                inGame = true;
            }

            if (score2 >= 11) {
                quit = true;
                win = false;
            } else if (score1 >= 11) {
                quit = true;
                win = true;
            }

            if (quit || shutDown) {
                ball->close();
                scorePlayer1->close();
                scorePlayer2->close();
            }
        }

        if (shutDown) {
            change();
            close(window);
        } else {
            change();
        }
    }

};