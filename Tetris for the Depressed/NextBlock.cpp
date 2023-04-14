#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "LTexture.cpp"

using std::vector;

class NextBlock {
private:
    const int neonEdge = 230;

public:
    LTexture *neon = new LTexture(neonEdge, neonEdge);
    int nextShape[4][2];
    LTexture* tiles;
    SDL_Rect indTile[8];
    
    void loadMedia (SDL_Renderer* renderer) {
        neon->loadFromFile("Graphics/Neon_square.png", renderer);
        tiles = new LTexture(22 * 8, 22);
        tiles->loadFromFile("Graphics/tiles.png", renderer);

        for (int i = 0; i < 8; i++) {
            indTile[i].x = 18 * i;
            indTile[i].y = 0;
            indTile[i].w = 18;
            indTile[i].h = 18;
        }
    }

    void render (int x, int y, SDL_Renderer* renderer, vector <SDL_Point> nextShapeArr, int nxtColorIdx) {
        for (int i = 0; i < 4; i++) {
            nextShape[nextShapeArr[i].y][nextShapeArr[i].x - 4] = nxtColorIdx;
        }
        neon->render(x, y, renderer);
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 2; j++) {
                if (nextShape[i][j] > 0) {
                    tiles->render(j * 22 + x + 90, i * 22 + y + 80, renderer, &indTile[nextShape[i][j]]);
                }
            }
        }
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 2; j++) {
                nextShape[i][j] = 0;
            }
        }
    }
};