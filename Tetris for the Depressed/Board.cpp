#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "Shape.cpp"

using std::string;
using std::cout;
using std::endl;
using std::to_string;
using std::vector;

class Board {
    private:

        LTexture* tiles;
        SDL_Point arr[4];
        SDL_Rect indTile[8];

    public:
        Board (SDL_Renderer* &renderer) {
            loadMedia(renderer);
        }

        void loadMedia (SDL_Renderer* &renderer) {
            tiles = new LTexture();
            tiles->loadFromFile("Graphics/tiles.png", renderer);

            for (int i = 0; i < 8; i++) {
                indTile[i].x = 18 * i;
                indTile[i].y = 0;
                indTile[i].w = 18;
                indTile[i].h = 18;
            }
        }

        void handleEvent (SDL_Event e, Shape* shape, vector <vector <int>>& board, bool& merge) {
            if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_LEFT:
                        shape -> moveLeft(board);
                        break;
                    case SDLK_RIGHT:
                        shape -> moveRight(board);
                        break;
                    case SDLK_UP:
                        shape->rotateUp(board);
                        break;
                    case SDLK_DOWN:
                        shape -> rotateDown(board);
                        break;
                    case SDLK_SPACE:
                        shape->hardDrop(board, merge);
                        break;
                }
            }
        }

        void render (vector <vector <int>>& board, SDL_Renderer* renderer) {
            for (int i = 0; i < PLAY_ROW; i++) {
                for (int j = 0; j < PLAY_COL; j++) {
                    if (board[i][j] != 0) {
                        if (board[i][j] < 10) {
                            tiles->render(j * 18 + 28, i * 18 + 31, renderer, &indTile[board[i][j]]);
                        } else {
                            tiles->render(j * 18 + 28, i * 18 + 31, renderer, &indTile[board[i][j] - 10]);
                        }
                    }
                }
            }
        }

        bool isGameOver (vector <vector <int>> & board) {
            for (int i = 0; i < PLAY_COL; i++) {
                if (board[0][i] >= 10) {
                    return true;
                }
            }
            return false;
        }

        void clearLines(vector <vector<int>>& board, vector <bool>& rowState) {
            for (int i = 0; i < PLAY_ROW; i++) {
                bool clear = true;
                rowState[i] = true;
                for (int j = 0; j < PLAY_COL; j++) {
                    if (board[i][j] < 10) {
                        clear = false;
                        rowState[i] = false;

                    }
                } 
                if (clear) {
                    for (int j = 0; j < PLAY_COL; j++) {
                        board[i][j] = 0;
                    }
                }
            }
            for (int i = PLAY_ROW - 2; i >= 0; i--) {
                if (!rowState[i]) {
                    int idx = i;
                    int curRow = idx;
                    while (idx < PLAY_ROW && rowState[++idx]) {
                        // get to the lowest clear lines
                    }        
                    idx --;
                    for (int j = 0; j < PLAY_COL; j++) {
                        if (board[curRow][j] >= 10) {
                            board[idx][j] = board[curRow][j];
                        }
                    }
                    if (idx != curRow) {
                        for (int j = 0; j < PLAY_COL; j++) {
                            board[curRow][j] = 0;
                        }
                        rowState[curRow] = true;
                        rowState[idx] = false;
                    }
                }
            }
        }
};