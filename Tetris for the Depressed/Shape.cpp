#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "LTexture.cpp"

using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::max;
using std::min;
using std::to_string;

class Shape {
    private:
        vector <vector <int>> shapes = {
            {1, 3, 5, 7}, 
            {0, 2, 3, 5}, 
            {1, 3, 2, 4}, 
            {1, 3, 2, 5}, 
            {0, 3, 2, 5},
            {1, 3, 5, 4},
            {0, 2, 1, 3}
        };

        SDL_Point prevShapeArr[4];

        int colorIdx;

    public:
        SDL_Point shapeArr[4];

        void fall () {
            for (int i = 0; i < 4; i++) {
                shapeArr[i].y ++;
            }
        } 

        bool checkMerge (vector <vector <int>>& board) {
            for (int i = 0; i < 4; i++) {
                if (shapeArr[i].y == PLAY_ROW) {
                    return true;
                }
            }
            bool check = false;
            int lowestPoint = - 10;
            for (int i = 0; i < 4; i++) {
                lowestPoint = max (lowestPoint, shapeArr[i].y);
            }

            for (int i = 0; i < 4; i++) {
                if (shapeArr[i].y == lowestPoint) {
                    if (board[shapeArr[i].y + 1][shapeArr[i].x] != 0) {
                        check = true;
                    } 
                }
            }
            return check;
        }

        void rotateDown () {
            for (int i = 0; i < 4; i++) {
                prevShapeArr[i] = shapeArr[i];
            }
            SDL_Point center = shapeArr[1];
            int orgiX = shapeArr[0].x;
            shapeArr[0].x = center.x + (shapeArr[0].y - center.y);
            shapeArr[0].y = center.y - (orgiX - center.x);
            for (int i = 2; i < 4; i++) {
                int orgiX = shapeArr[i].x;
                shapeArr[i].x = center.x + (shapeArr[i].y - center.y);
                shapeArr[i].y = center.y - (orgiX - center.x);
            }
        }

        void rotateUp () {
            for (int i = 0; i < 4; i++) {
                prevShapeArr[i] = shapeArr[i];
            }
            SDL_Point center = shapeArr[1];
            int orgiX = shapeArr[0].x;
            shapeArr[0].x = center.x - (shapeArr[0].y - center.y);
            shapeArr[0].y = center.y + (orgiX - center.x);
            for (int i = 2; i < 4; i++) {
                orgiX = shapeArr[i].x;
                shapeArr[i].x = center.x - (shapeArr[i].y - center.y);
                shapeArr[i].y = center.y + (orgiX - center.x);
            }
        }

        void moveLeft () {
            for (int i = 0; i < 4; i++) {
                shapeArr[i].x --;
            }
        }

        void moveRight () {
            for (int i = 0; i < 4; i++) {
                shapeArr[i].x ++;
            }
        }

        void undoChange () {
            for (int i = 0; i < 4; i++) {
                shapeArr[i] = prevShapeArr[i];
            }
        }

        void updateBoard (vector<vector<int>>& board) {
            for (int i = 0; i < 4; i++) {
                board[prevShapeArr[i].y][prevShapeArr[i].x] = 0;
            }
            for (int i = 0; i < 4; i++) {
                board[shapeArr[i].y][shapeArr[i].x] = colorIdx;
                prevShapeArr[i] = shapeArr[i];
            }
        }

        int getColorIdx () {
            return colorIdx;
        }

        Shape () {
            int shapeIdx = rand() % 7;
            colorIdx = rand() % 8;

            for (int i = 0; i < 4; i++) {
                shapeArr[i].x = shapes[shapeIdx][i] % 2 + 4;
                shapeArr[i].y = shapes[shapeIdx][i] / 2;

                prevShapeArr[i].x = shapeArr[i].x;
                prevShapeArr[i].y = shapeArr[i].y;
            }
        }
};