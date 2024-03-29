#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "LTexture.h"
#include "Shape.h"
#include "Constants.h"

using std::cout;
using std::endl;
using std::string;
using std::to_string;
using std::vector;

// The board is saved as a 2-d array of int
// The integer is used to render blocks and colors (each int represent a color)
// 0 means that there is nothing in that block
// -1 is used to form white lines to represent where the block will fall down
// Integer < 10 is used to represent blocks that is in play
// While integer > 10 represent blocks that has been locked (the surface)
class Board
{
private:
    LTexture *tiles;
    SDL_Point arr[4];
    SDL_Rect indTile[8];

    Mix_Chunk *clearLineSound = NULL;
    Mix_Chunk *clearMultipleSound = NULL;

public:
    Board(SDL_Renderer *&renderer);
    ~Board();
    void loadMedia(SDL_Renderer *&renderer);
    void handleEvent(SDL_Event e, Shape *shape, vector<vector<int>> &board, bool &merge, double &systemVolume);
    void render(vector<vector<int>> &board, SDL_Renderer *renderer);
    void clearHover(vector<vector<int>> &board);
    bool isGameOver(vector<vector<int>> &board);
    void clearLines(vector<vector<int>> &board, vector<bool> &rowState, int &lines, int &score, int &highScore, double &systemVolume);
};

#endif