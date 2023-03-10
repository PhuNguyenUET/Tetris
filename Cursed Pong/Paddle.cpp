#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "Ball.cpp"

using std::string;
using std::cout;
using std::endl;


class Paddle {
    public:
    static const int PWIDTH = 12;
    static const int PHEIGHT = 60;
    const double PADDLE_VEL = 0.3 ;

    Paddle (double pX) {
        this -> pX = pX;
        pCollider.x = pX;
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

    void selfMove (SDL_Rect pad, Ball* b) {
        SDL_Rect ball = b->getCollider();
        int bTop = ball.y;
        int bBot = ball.y + ball.h;

        int pTop = pad.y;
        int pBot = pad.y + pad.h;

        if (pTop > bBot) {
            pVelY = -PADDLE_VEL; 
        } else if (pBot < bTop) {
            pVelY = PADDLE_VEL;
        } else {
            pVelY = 0;
        }

        // If the ball is moving in a straight line
        // And the AI is not moving
        if ((*b).getVelY() == 0 && pVelY == 0) {
            int status = (*b).collisionPos(ball, pad);
            // Prevent the AI to hit in a straight line again
            // By checking if it does then change the velocity
            // If the upper-half, then move down
            // If the lower-half, then move up
            if (status == 2) {
                if (pad.y < SCREEN_HEIGHT/2) {
                    pVelY = PADDLE_VEL;
                } else {
                    pVelY = - PADDLE_VEL;
                }
            }
        }

        pY = pY + pVelY;
        pCollider.y = pY;
        if ((pY < 0) || (pY + PHEIGHT > SCREEN_HEIGHT)) {
            pY -= pVelY;
            pCollider.y = pY;
            pVelY = 0;
        }
    }

    void forceStop () {
        pVelY = 0;
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