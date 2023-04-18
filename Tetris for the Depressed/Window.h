#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <vector>
#include <fstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

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
        LTexture* tutorial = NULL;
        ScoreBoard* scoreBoard;
        EndGameNoti* endGameNoti;
        NextBlock* nxtBlock = new NextBlock();

        Mix_Chunk *endGameSound = NULL;
        Mix_Music *themeSong = NULL;

        vector <SDL_Point> nextShapeArr = vector <SDL_Point>(4);
        vector <int> shapeRotation = {1, 1, 1, 1, 1, 1, 1};
        int nxtColorIdx;
        int highScore;
        Shape* shape;
        Board* brd;

        bool end = false;

        void init (SDL_Window* &window);
        void loadMedia (int songIdx);
        void close ();
        void kill (SDL_Window* &window);
    public:
        vector <vector <int>> board;
        vector <bool> rowState;

        Window (SDL_Window* &window, bool& quit, bool& playNext, double& systemVolume, double& musicVolume, int& songIdx, bool& turnBack);
};

#endif