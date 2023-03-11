#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "Board.cpp"
#include "ScoreBoard.cpp"

using std::string;
using std::cout;
using std::endl;
using std::to_string;


class Window {
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        LTexture* bg = NULL;
        ScoreBoard* lineBoard;
        ScoreBoard* scoreBoard;

        Shape* shape;
        Board* brd;

        void init () {
            SDL_Init(SDL_INIT_EVERYTHING);
            SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

            window = SDL_CreateWindow("Tetris for the Depressed", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

            int imgFlag = IMG_INIT_PNG;
            IMG_Init(imgFlag);
        }

        void loadMedia () {
            bg = new LTexture(SCREEN_WIDTH, SCREEN_HEIGHT);
            bg->loadFromFile("Graphics/background.png", renderer);
        }

        void close () {
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            renderer = NULL;
            window = NULL;

            IMG_Quit();
            SDL_Quit();
        }

    public:
        vector <vector <int>> board;
        vector <bool> rowState;

        Window () {
            for (int i = 0; i < PLAY_ROW; i++) {
                vector <int> tmp;
                for (int j = 0; j < PLAY_COL; j++) {
                    tmp.push_back (0);
                }
                board.push_back(tmp);
                rowState.push_back(true);
            }

            init ();
            loadMedia();

            bool quit = false;
            bool startCount = true;
            SDL_Event e;
            int prevTime = 0;
            int lines = 0;
            int score = 0;
            int prevLines = lines;
            int prevScore = score;
            int prevLockTime = 0;

            shape = new Shape(board, quit);
            brd = new Board(renderer);
            scoreBoard = new ScoreBoard(170, 50);
            lineBoard = new ScoreBoard(110, 50);

            scoreBoard->loadFromRenderedText("Your score: " + to_string(score), renderer);
            scoreBoard->render((SCREEN_WIDTH - 170) / 2, SCREEN_HEIGHT - 80, renderer);

            lineBoard->loadFromRenderedText("Lines: " + to_string(lines), renderer);
            lineBoard->render((SCREEN_WIDTH - 120) / 2, SCREEN_HEIGHT - 120, renderer);

            while (!quit) {
                int time = SDL_GetTicks();
                bool merge = false;
                while (SDL_PollEvent(&e)) {
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    } else {
                        brd->handleEvent(e, shape, board, merge);
                    }
                }

                if (score != prevScore) {
                    scoreBoard->loadFromRenderedText("Your score: " + to_string(score), renderer);
                    prevScore = score;
                }

                if (lines != prevLines) {
                    lineBoard->loadFromRenderedText("Lines: " + to_string(lines), renderer);
                    prevLines = lines;
                }

                if (time - prevTime >= 700) {
                    if (!shape->checkMerge(board)) {  
                        shape->fall(startCount);
                    }
                    prevTime = time;
                }

                if (startCount) {
                    prevLockTime = time;
                }

                if (merge) {
                    shape->updateBoard(board);
                    shape->merge(board);
                    shape = new Shape(board, quit);
                } else if (shape->checkMerge(board)) {
                    startCount = false;
                    if (time - prevLockTime >= 500) {
                        shape->updateBoard(board);
                        shape->merge(board);
                        shape = new Shape(board, quit);
                        startCount = true;
                    }
                }

                if (brd->isGameOver(board)) {
                    quit = true;
                }

                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderClear(renderer);

                bg->render(0, 0, renderer);

                shape->updateBoard(board);

                scoreBoard->render((SCREEN_WIDTH - 170) / 2, SCREEN_HEIGHT - 80, renderer);
                lineBoard->render((SCREEN_WIDTH - 120) / 2, SCREEN_HEIGHT - 120, renderer);

                brd->clearLines(board, rowState, lines, score);
                brd->render(board, renderer);

                SDL_RenderPresent(renderer);
            }
            close ();
        }
};