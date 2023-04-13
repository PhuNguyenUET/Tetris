#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "Board.cpp"

using std::string;
using std::cout;
using std::endl;
using std::to_string;


class Window {
    private:
        SDL_Renderer* renderer;
        LTexture* bg = NULL;
        ScoreBoard* scoreBoard;
        EndGameNoti* endGameNoti;

        Shape* shape;
        Board* brd;

        bool end = false;

        void init (SDL_Window* &window) {
            SDL_Init(SDL_INIT_EVERYTHING);
            SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

            int imgFlag = IMG_INIT_PNG;
            IMG_Init(imgFlag);
        }

        void loadMedia () {
            bg = new LTexture(SCREEN_WIDTH, SCREEN_HEIGHT);
            bg->loadFromFile("Graphics/Tetris_BackGround.png", renderer);
        }

        void close () {
            SDL_DestroyRenderer(renderer);
            renderer = NULL;

            IMG_Quit();
        }

        void kill (SDL_Window* &window) {
            SDL_DestroyWindow(window);
            window = NULL;

            SDL_Quit();
        }

    public:
        vector <vector <int>> board;
        vector <bool> rowState;

        Window (SDL_Window* &window, bool& quit, bool& playNext) {
            for (int i = 0; i < PLAY_ROW; i++) {
                vector <int> tmp;
                for (int j = 0; j < PLAY_COL; j++) {
                    tmp.push_back (0);
                }
                board.push_back(tmp);
                rowState.push_back(true);
            }

            init (window);
            loadMedia();

            bool startCount = true;
            SDL_Event e;
            int prevTime = 0;
            int lines = 0;
            int score = 0;
            int prevLines = lines;
            int prevScore = score;
            int prevLockTime = 0;

            shape = new Shape(board, end);
            brd = new Board(renderer);
            scoreBoard = new ScoreBoard(170, 50 , 110, 50, renderer);
            
            LTexture* playArea = new LTexture(22* 10, 22*20);
            playArea->loadFromFile("Graphics/PlayArea.png", renderer);

            scoreBoard->loadFromRenderedText("Your score: " + to_string(score), "Lines: " + to_string(lines), renderer);
            scoreBoard->render(SCREEN_WIDTH - 350, 300, renderer);

            while (!quit && !end) {
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
                    scoreBoard->loadFromRenderedText("Your score: " + to_string(score), "Lines: " + to_string(lines), renderer);
                    prevScore = score;
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
                    shape = new Shape(board, end);
                } else if (shape->checkMerge(board)) {
                    startCount = false;
                    if (time - prevLockTime >= 500) {
                        shape->updateBoard(board);
                        shape->merge(board);
                        shape = new Shape(board, end);
                        startCount = true;
                    }
                }

                if (brd->isGameOver(board)) {
                    end = true;
                }

                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderClear(renderer);

                bg->render(0, 0, renderer);
                playArea->render(490, 47, renderer);

                shape->hover(board, merge);
                shape->updateBoard(board);

                scoreBoard->render(SCREEN_WIDTH - 350, 300, renderer);

                brd->clearLines(board, rowState, lines, score);
                brd->render(board, renderer);

                /*SDL_SetRenderDrawColor(renderer, 51, 153, 255, 255);
                for (int i = 0; i <= 10; i ++) {
                    SDL_RenderDrawLine(renderer, 490 + 22*i, 47, 490 + 22*i, 47 + 22 * 20);
                }
                for (int j = 0; j <= 20; j++) {
                    SDL_RenderDrawLine(renderer, 490, 47 + j * 22, 490 + 22*10, 47 + j * 22);
                }*/

                brd->clearHover(board);

                SDL_RenderPresent(renderer);
            }
            if (quit) {
                close ();
                kill(window);
            } else {
                endGameNoti = new EndGameNoti(renderer);

                while (!quit && !playNext) {
                    while (SDL_PollEvent(&e)) {
                        if (e.type == SDL_QUIT) {
                            quit = true;
                        } else {
                            endGameNoti->handleEvent(e, playNext);
                        }
                    }

                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                    SDL_RenderClear(renderer);
                    bg->render(0, 0, renderer);
                    playArea->render(490, 47, renderer);

                    brd->render(board, renderer);

                    scoreBoard->render(SCREEN_WIDTH - 350, 300, renderer);

                    endGameNoti->render(30, 200, renderer);

                    SDL_RenderPresent(renderer);
                }

                scoreBoard->close();
                endGameNoti->close();
                if (quit) {
                    close ();
                    kill (window);
                } else {
                    close();
                }
            }
        }
};