#ifndef SHAPE_H
#define SHAPE_H

#include <iostream>
#include <vector>
#include <cmath>
#include <SDL2/SDL_mixer.h>
#include <algorithm>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "Constants.h"

using std::cout;
using std::endl;
using std::max;
using std::min;
using std::string;
using std::to_string;
using std::vector;

class Shape
{
private:
    // The 7 shapes are saved in a 2x4 grid
    vector<vector<int>> shapes = {
        {1, 3, 5, 7},
        {0, 2, 4, 5},
        {1, 3, 2, 4},
        {1, 3, 2, 5},
        {0, 3, 2, 5},
        {1, 3, 5, 4},
        {0, 2, 1, 3}};

    // A prev shape is memorized in case the move is invalid and we need to return
    SDL_Point prevShapeArr[4];

    int colorIdx;

    Mix_Chunk *hardDropSound = NULL;

public:
    // The shape Array, representing the shape that is in play
    SDL_Point shapeArr[4];
    void fall(bool &startCount);
    bool checkMerge(vector<vector<int>> &board);
    void rotateDown(vector<vector<int>> &board);
    void rotateUp(vector<vector<int>> &board);
    void merge(vector<vector<int>> &board);
    bool checkValidMove(vector<vector<int>> &board);
    void moveLeft(vector<vector<int>> &board);
    void moveRight(vector<vector<int>> &board);
    void undoChange();
    void updateBoard(vector<vector<int>> &board);
    void hardDrop(vector<vector<int>> &board, bool &merge, double &systemVolume);
    void hover(vector<vector<int>> &board, bool &merge);
    void loadMedia();
    int getColorIdx();
    void generateNextBlock(vector<SDL_Point> &nextShapeArr, vector<int> &shapeRotation, int &nxtColorIdx);
    Shape(vector<int> &shapeRotation);
    Shape(vector<vector<int>> &board, bool &end, vector<SDL_Point> &nextShapeArr, int &nxtColorIdx);
    ~Shape();
};

#endif