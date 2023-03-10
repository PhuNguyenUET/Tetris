#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

using std::string;
using std::cout;
using std::endl;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

class Paddle {
    public:
    static const int PWIDTH = 20;
    static const int PHEIGHT = 100;
    const double PADDLE_VEL = 0.4;

    Paddle (double pX) {
        this -> pX = pX;
        pY = 0;
        pVelY = 0;
        pCollider.w = PWIDTH;
        pCollider.h = PHEIGHT;
    }

    SDL_Rect getCollider () {
        return pCollider;
    }

    void render (SDL_Renderer*& renderer)  {
        SDL_Rect pad = {pX, pY, PWIDTH, PHEIGHT};
        SDL_SetRenderDrawColor (renderer, 255, 255, 255, 255);
        SDL_RenderFillRect (renderer, &pad);
    }

    void move () {
        pY += pVelY;
        pCollider.y = pY;
        if ((pY < 0) || (pY + PHEIGHT > SCREEN_HEIGHT)) {
            pY -= pVelY;
            pCollider.y = pY;
        }
    }

    void handleEvent (SDL_Event& e) {
        if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
            switch(e.key.keysym.sym) {
                case SDLK_UP:
                    pVelY -= PADDLE_VEL;
                    break;
                case SDLK_DOWN:
                    pVelY += PADDLE_VEL;
                    break;
            }
        }

        if (e.type == SDL_KEYUP && e.key.repeat == 0) {
            switch (e.key.keysym.sym) {
                case SDLK_UP:
                    pVelY += PADDLE_VEL;
                    break;
                case SDLK_DOWN:
                    pVelY -= PADDLE_VEL;
                    break;
            }
        }
    }

    private: 
    double pX;
    double pY;

    double pVelY;

    SDL_Rect pCollider;
};