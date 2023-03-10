#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

using std::string;
using std::cout;
using std::endl;

const int SCREEN_WIDTH_B = 800;
const int SCREEN_HEIGHT_B = 600;

class Ball {
    public:
        static const int BALL_WIDTH = 15;
        static const int BALL_HEIGHT = 15;
        double bVelDif = 0.5;
        Ball () {
            bX = (SCREEN_WIDTH_B - BALL_WIDTH) / 2;
            bY = (SCREEN_HEIGHT_B - BALL_HEIGHT) / 2;

            bVelDif = 0.5;

            bVelX = -0.1;
            bVelY = -0.1;
        }

        void move (SDL_Rect const &pad1, SDL_Rect const &pad2) {
            bX += bVelX;
            bCollider.x = bX;

            if (checkCollision(bCollider, pad1) || checkCollision(bCollider, pad2)) {
                bX -= bVelX;
                bCollider.x = bX;

                bVelX = -bVelX;
            }

            bY += bVelY;
            bCollider.y = bY;

            if (bY < 0 || (bY + BALL_HEIGHT > SCREEN_HEIGHT_B)) {
                bY -= bVelY;
                bCollider.y = bY;

                bVelY = -bVelY;
            }
        }

        bool checkCollision (SDL_Rect ball, SDL_Rect pad) {
            int bLeft, bRight;
            int pLeft, pRight;
            int bTop, bBot;
            int pTop, pBot;

            bLeft = ball.x;
            bRight = ball.x + ball.w;
            bTop = ball.y;
            bBot = ball.y + ball.h;

            pLeft = pad.x;
            pRight = pad.x + pad.w;
            pTop = pad.y;
            pBot = pad.y + pad.h;

            if (bBot < pTop) {
                return false;
            } else if (bTop > pBot) {
                return false;
            } else if (bRight < pLeft) {
                return false;
            } else if (bLeft > pRight) {
                return false;
            }

            return true;
        }

        void render (SDL_Renderer*& renderer) {
            SDL_Rect pad = {bX, bY, BALL_WIDTH, BALL_HEIGHT};
            SDL_SetRenderDrawColor (renderer, 255, 255, 255, 255);
            SDL_RenderFillRect (renderer, &pad);
        }

        SDL_Rect getCollider () {
            return bCollider;
        }

    private:
        double bX;
        double bY;
        double bVelX;
        double bVelY;
        SDL_Rect bCollider;
};