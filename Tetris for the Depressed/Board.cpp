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

        void handleEvent (SDL_Event e, Shape* shape) {
            if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_LEFT:
                        shape -> moveLeft();
                        break;
                    case SDLK_RIGHT:
                        shape -> moveRight();
                        break;
                    case SDLK_UP:
                        shape->rotateUp();
                        break;
                    case SDLK_DOWN:
                        shape -> rotateDown();for (int j = 0; j < PLAY_COL; j++) {
                    
                }
                        break;
                    case SDLK_SPACE:
                        shape->fall();
                        break;
                }
            }
        }

        void checkValidMove() {
            
        }

        void render (vector <vector <int>>& board, SDL_Renderer* renderer, int colorIdx) {
            for (int i = 0; i < PLAY_ROW; i++) {
                for (int j = 0; j < PLAY_COL; j++) {
                    if (board[i][j] != 0) {
                        tiles->render(j * 18, i * 18, renderer, &indTile[colorIdx]);
                    }
                }
            }
        }

        bool isGameOver (Shape shape, vector <vector <int>> & board) {
            if (shape.checkMerge (board)) {
                for (int i = 0; i < 4; i++) {
                    if (shape.shapeArr[i].y <= 0) {
                        return true;
                    }
                }
            }
            return false;
        }

        void clearLines(vector <vector<int>>& board, vector <bool>& rowState) {
            for (int i = 0; i < PLAY_ROW; i++) {
                bool clear = true;
                rowState[i] = true;
                for (int j = 0; j < PLAY_COL; j++) {
                    if (board[i][j] == 0) {
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
                int idx = i;
                int curRow = idx;
                while (idx < PLAY_ROW && rowState[idx ++]) {
                    // get to the lowest clear lines
                }        
                idx --;
                board[idx] = board[curRow];
                board[curRow] = vector <int> (PLAY_COL, 0); 
            }
        }

        void hardDrop () {

        }
};