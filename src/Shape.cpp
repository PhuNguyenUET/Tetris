#include <iostream>

#include "../Header/Shape.h"

void Shape::fall(bool &startCount)
{
    for (int i = 0; i < 4; i++)
    {
        shapeArr[i].y++;
    }
    startCount = true;
}

bool Shape::checkMerge(vector<vector<int>> &board)
{
    // Hit the bottom
    for (int i = 0; i < 4; i++)
    {
        if (shapeArr[i].y == PLAY_ROW - 1)
        {
            return true;
        }
    }
    bool check = false;
    // Hit the surface
    for (int i = 0; i < 4; i++)
    {
        if (board[shapeArr[i].y + 1][shapeArr[i].x] >= 10)
        {
            check = true;
        }
    }
    return check;
}

void Shape::rotateDown(vector<vector<int>> &board)
{
    // Remember the current shape before rotating
    for (int i = 0; i < 4; i++)
    {
        prevShapeArr[i] = shapeArr[i];
    }
    // The center to rotate
    SDL_Point center = shapeArr[1];
    // The mathematics to rotate the shapes (Matrix inverse and transpose)
    int orgiX = shapeArr[0].x;
    shapeArr[0].x = center.x + (shapeArr[0].y - center.y);
    shapeArr[0].y = center.y - (orgiX - center.x);
    for (int i = 2; i < 4; i++)
    {
        int orgiX = shapeArr[i].x;
        shapeArr[i].x = center.x + (shapeArr[i].y - center.y);
        shapeArr[i].y = center.y - (orgiX - center.x);
    }
    // If the rotation isn't valid, then undo the change
    if (!checkValidMove(board))
    {
        undoChange();
    }
}

// Similar to rotate down
void Shape::rotateUp(vector<vector<int>> &board)
{
    for (int i = 0; i < 4; i++)
    {
        prevShapeArr[i] = shapeArr[i];
    }
    SDL_Point center = shapeArr[1];
    int orgiX = shapeArr[0].x;
    shapeArr[0].x = center.x - (shapeArr[0].y - center.y);
    shapeArr[0].y = center.y + (orgiX - center.x);
    for (int i = 2; i < 4; i++)
    {
        orgiX = shapeArr[i].x;
        shapeArr[i].x = center.x - (shapeArr[i].y - center.y);
        shapeArr[i].y = center.y + (orgiX - center.x);
    }
    if (!checkValidMove(board))
    {
        undoChange();
    }
}

// Update the int grid to merge
void Shape::merge(vector<vector<int>> &board)
{
    for (int i = 0; i < 4; i++)
    {
        board[shapeArr[i].y][shapeArr[i].x] = colorIdx + 10;
    }
}

bool Shape::checkValidMove(vector<vector<int>> &board)
{
    for (int i = 0; i < 4; i++)
    {
        if (shapeArr[i].x < 0 || shapeArr[i].x >= PLAY_COL || board[shapeArr[i].y][shapeArr[i].x] >= 10)
        {
            return false;
        }
    }
    return true;
}

void Shape::moveLeft(vector<vector<int>> &board)
{
    for (int i = 0; i < 4; i++)
    {
        prevShapeArr[i] = shapeArr[i];
    }
    for (int i = 0; i < 4; i++)
    {
        shapeArr[i].x--;
    }
    if (!checkValidMove(board))
    {
        undoChange();
    }
}

void Shape::moveRight(vector<vector<int>> &board)
{
    for (int i = 0; i < 4; i++)
    {
        prevShapeArr[i] = shapeArr[i];
    }
    for (int i = 0; i < 4; i++)
    {
        shapeArr[i].x++;
    }
    if (!checkValidMove(board))
    {
        undoChange();
    }
}

void Shape::undoChange()
{
    for (int i = 0; i < 4; i++)
    {
        shapeArr[i] = prevShapeArr[i];
    }
}

void Shape::updateBoard(vector<vector<int>> &board)
{
    // Clear the previous state
    for (int i = 0; i < 4; i++)
    {
        if (board[prevShapeArr[i].y][prevShapeArr[i].x] < 10)
        {
            board[prevShapeArr[i].y][prevShapeArr[i].x] = 0;
        }
    }
    // Update the current state
    for (int i = 0; i < 4; i++)
    {
        if (board[shapeArr[i].y][shapeArr[i].x] < 10)
        {
            board[shapeArr[i].y][shapeArr[i].x] = colorIdx;
            prevShapeArr[i] = shapeArr[i];
        }
        else
        {
            // The surface -> can't update
            break;
        }
    }

    // Fix the dragging bug after updating
    // Check each cell to ensure that it is part of the shape
    for (int i = 0; i < PLAY_ROW; i++)
    {
        for (int j = 0; j < PLAY_COL; j++)
        {
            if (board[i][j] < 10 && board[i][j] > 0)
            {
                bool check = true;
                for (int k = 0; k < 4; k++)
                {
                    if (shapeArr[k].y == i && shapeArr[k].x == j)
                    {
                        check = false;
                    }
                }
                if (check)
                {
                    board[i][j] = 0;
                }
            }
        }
    }
}

void Shape::hardDrop(vector<vector<int>> &board, bool &merge, double &systemVolume)
{
    // Dropping the shape to the lowest possible
    while (true)
    {
        bool brk = false;
        for (int i = 0; i < 4; i++)
        {
            if (shapeArr[i].y == PLAY_ROW - 1)
            {
                brk = true;
                break;
            }

            if (board[shapeArr[i].y + 1][shapeArr[i].x] >= 10)
            {
                brk = true;
                break;
            }
        }
        if (brk)
        {
            break;
        }
        for (int i = 0; i < 4; i++)
        {
            shapeArr[i].y++;
        }
    }
    merge = true;
    Mix_VolumeChunk(hardDropSound, MIX_MAX_VOLUME * systemVolume);
    Mix_PlayChannel(-1, hardDropSound, 0);
}

// Similar to hard-drop but we drop a fake temporary block to check the position
void Shape::hover(vector<vector<int>> &board, bool &merge)
{
    SDL_Point whiteLines[4];
    for (int i = 0; i < 4; i++)
    {
        whiteLines[i].x = shapeArr[i].x;
        whiteLines[i].y = shapeArr[i].y;
    }
    if (!merge)
    {
        while (true)
        {
            bool brk = false;
            for (int i = 0; i < 4; i++)
            {
                if (whiteLines[i].y == PLAY_ROW - 1)
                {
                    brk = true;
                    break;
                }

                if (board[whiteLines[i].y + 1][whiteLines[i].x] >= 10)
                {
                    brk = true;
                    break;
                }
            }
            if (brk)
            {
                break;
            }
            for (int i = 0; i < 4; i++)
            {
                whiteLines[i].y++;
            }
        }
        for (int i = 0; i < 4; i++)
        {
            board[whiteLines[i].y][whiteLines[i].x] = -1;
        }
    }
}

void Shape::loadMedia()
{
    hardDropSound = Mix_LoadWAV("Audio/HardDrop.wav");
}

int Shape::getColorIdx()
{
    return colorIdx;
}

// Generate next block to go into next block window
void Shape::generateNextBlock(vector<SDL_Point> &nextShapeArr, vector<int> &shapeRotation, int &nxtColorIdx)
{
    int shapeIdx;
    // Check to see if the batch of 7 has been all released
    bool check = true;
    for (int i = 0; i < 7; i++)
    {
        if (shapeRotation[i] == 1)
        {
            check = false;
        }
    }
    // If yes, generate a new batch
    if (check)
    {
        for (int i = 0; i < 7; i++)
        {
            shapeRotation[i] = 1;
        }
    }
    // generate a random block in the batch of 7
    do
    {
        shapeIdx = rand() % 7;
    } while (shapeRotation[shapeIdx] == 0);
    // Random color
    nxtColorIdx = rand() % 7 + 1;

    // This is the array to track the batch
    shapeRotation[shapeIdx] = 0;

    // Generate the shape array
    // Convert from the 2x4 grid shape to the xy shape
    for (int i = 0; i < 4; i++)
    {
        nextShapeArr[i].x = shapes[shapeIdx][i] % 2 + 4;
        nextShapeArr[i].y = shapes[shapeIdx][i] / 2;
    }
}

// First shape in the game
Shape::Shape(vector<int> &shapeRotation)
{
    int shapeIdx = rand() % 7;
    colorIdx = rand() % 7 + 1;

    shapeRotation[shapeIdx] = 0;

    for (int i = 0; i < 4; i++)
    {
        shapeArr[i].x = shapes[shapeIdx][i] % 2 + 4;
        shapeArr[i].y = shapes[shapeIdx][i] / 2;

        prevShapeArr[i].x = shapeArr[i].x;
        prevShapeArr[i].y = shapeArr[i].y;
    }
    loadMedia();
}

// Taking the shape from next shape
Shape::Shape(vector<vector<int>> &board, bool &end, vector<SDL_Point> &nextShapeArr, int &nxtColorIdx)
{
    colorIdx = nxtColorIdx;
    for (int i = 0; i < 4; i++)
    {
        shapeArr[i].x = nextShapeArr[i].x;
        shapeArr[i].y = nextShapeArr[i].y;

        prevShapeArr[i].x = shapeArr[i].x;
        prevShapeArr[i].y = shapeArr[i].y;

        // Check endgame
        if (board[shapeArr[i].y][shapeArr[i].x] >= 10)
        {
            end = true;
        }
    }
    loadMedia();
}

Shape::~Shape()
{
    Mix_FreeChunk(hardDropSound);
    hardDropSound = NULL;
}
