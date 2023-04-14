#include <iostream>
#include <vector>
#include <fstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "Board.cpp"

using std::string;
using std::cout;
using std::endl;
using std::to_string;
using std::vector;


class Window {
    private:
        SDL_Renderer* renderer;
        LTexture* bg = NULL;
        LTexture* endGame = NULL;
        ScoreBoard* scoreBoard;
        EndGameNoti* endGameNoti;
        NextBlock* nxtBlock = new NextBlock();

        Mix_Chunk *endGameSound = NULL;
        Mix_Music *themeSong = NULL;

        vector <SDL_Point> nextShapeArr = vector <SDL_Point>(4);
        int nxtColorIdx;
        int highScore;
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

            Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
        }

        void loadMedia (int songIdx) {
            bg = new LTexture(SCREEN_WIDTH, SCREEN_HEIGHT);
            bg->loadFromFile("Graphics/Tetris_BackGround.png", renderer);
            endGame = new LTexture(SCREEN_WIDTH, SCREEN_HEIGHT);
            endGame->loadFromFile("Graphics/EndGame.png", renderer);
            nxtBlock->loadMedia(renderer);

            endGameSound = Mix_LoadWAV("Audio/GameOver.wav");
            switch (songIdx) {
                case 0:
                    themeSong = Mix_LoadMUS("Audio/TetrisSoundTrackOriginal.wav");
                    break;
                case 1:
                    themeSong = Mix_LoadMUS("Audio/TetrisSoundTrackWithLyrics.wav");
                    break;
                case 2:
                    themeSong = Mix_LoadMUS("Audio/Dissipate.wav");
                    break;
                case 3:
                    themeSong = Mix_LoadMUS("Audio/Natsukashii.wav");
                    break;
            }
        }

        void close () {
            SDL_DestroyRenderer(renderer);
            renderer = NULL;

            Mix_FreeChunk(endGameSound);
            endGameSound = NULL;

            Mix_FreeMusic(themeSong);
            themeSong = NULL;

            Mix_Quit();
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

        Window (SDL_Window* &window, bool& quit, bool& playNext, double& systemVolume, double& musicVolume, int& songIdx) {
            std::fstream file ("HighScore.txt");
            file >> highScore;
            file.seekg(0);
            for (int i = 0; i < PLAY_ROW; i++) {
                vector <int> tmp;
                for (int j = 0; j < PLAY_COL; j++) {
                    tmp.push_back (0);
                }
                board.push_back(tmp);
                rowState.push_back(true);
            }

            init (window);
            loadMedia(songIdx);

            bool startCount = true;
            SDL_Event e;
            int prevTime = 0;
            int lines = 0;
            int score = 0;
            int prevLines = lines;
            int prevScore = score;
            int prevLockTime = 0;

            shape = new Shape();
            shape->generateNextBlock(nextShapeArr, nxtColorIdx);
            brd = new Board(renderer);
            scoreBoard = new ScoreBoard(170, 50 , 110, 50, renderer);
            
            LTexture* playArea = new LTexture(22* 10, 22*20);
            playArea->loadFromFile("Graphics/PlayArea.png", renderer);

            scoreBoard->loadFromRenderedText("Your score: " + to_string(score), "Lines: " + to_string(lines), "High score: " + to_string(highScore), renderer);
            scoreBoard->render(SCREEN_WIDTH - 350, 300, renderer);

            nxtBlock->render(SCREEN_WIDTH - 350, 50, renderer, nextShapeArr, nxtColorIdx);

            Mix_VolumeMusic(MIX_MAX_VOLUME * musicVolume);
            Mix_VolumeChunk(endGameSound, MIX_MAX_VOLUME * systemVolume);
            Mix_PlayMusic(themeSong, -1);

            while (!quit && !end) {
                int time = SDL_GetTicks();
                bool merge = false;
                while (SDL_PollEvent(&e)) {
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    } else {
                        brd->handleEvent(e, shape, board, merge, systemVolume);
                    }
                }

                if (score != prevScore) {
                    scoreBoard->loadFromRenderedText("Your score: " + to_string(score), "Lines: " + to_string(lines),"High score: " + to_string(highScore), renderer);
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
                    shape = new Shape(board, end, nextShapeArr, nxtColorIdx);
                    shape->generateNextBlock(nextShapeArr, nxtColorIdx);
                } else if (shape->checkMerge(board)) {
                    startCount = false;
                    if (time - prevLockTime >= 500) {
                        shape->updateBoard(board);
                        shape->merge(board);
                        shape = new Shape(board, end, nextShapeArr, nxtColorIdx);
                        shape->generateNextBlock(nextShapeArr, nxtColorIdx);
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
                nxtBlock->render(SCREEN_WIDTH - 350, 50, renderer, nextShapeArr, nxtColorIdx);

                brd->clearLines(board, rowState, lines, score, highScore, systemVolume);
                brd->render(board, renderer);

                brd->clearHover(board);

                SDL_RenderPresent(renderer);
            }
            if (score >= highScore) {
                file << score;
            }
            Mix_PlayChannel(-1, endGameSound, 0);
            Mix_HaltMusic();
            file.close();
            if (quit) {
                close ();
                kill(window);
            } else {
                endGameNoti = new EndGameNoti(renderer);

                endGameNoti->loadScore(score, highScore, renderer);

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
                    endGame->render(0, 0, renderer);

                    endGameNoti->render((SCREEN_WIDTH - 300) / 2, 150, renderer);

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