#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

using std::string;
using std::cout;
using std::endl;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

class Ball {
    public:
        static const int BALL_WIDTH = 12;
        static const int BALL_HEIGHT = 12;
        const double bIniVel = 0.1;
        double bVelDif = 0.5;
        int randDirection () {
            return rand() % 4 + 1;
        }
        Ball () {
            bX = (SCREEN_WIDTH - BALL_WIDTH) / 2;
            bY = (SCREEN_HEIGHT - BALL_HEIGHT) / 2;

            bCollider.w = BALL_WIDTH;
            bCollider.h = BALL_HEIGHT;

            bVelDif = 0.5;
            int dir = randDirection();
            switch (dir) {
                case 1:
                    bVelX = -bIniVel;
                    bVelY = -bIniVel;
                    break;
                case 2:
                    bVelX = bIniVel;
                    bVelY = -bIniVel;
                    break;
                case 3:
                    bVelX = bIniVel;
                    bVelY = bIniVel;
                    break;
                case 4:
                    bVelX = -bIniVel;
                    bVelY = bIniVel;
                    break;
            }
        }


        void move (SDL_Rect const &pad1, SDL_Rect const &pad2) {
            bX += bVelX;
            bCollider.x = bX;

            if (checkCollision(bCollider, pad1) || checkCollision(bCollider, pad2)) {
                bool p1 = checkCollision(bCollider, pad1);
                bool p2 = checkCollision(bCollider, pad2);
                int state;
                if (p1) {
                    state = collisionPos(bCollider, pad1);
                } else if (p2) {
                    state = collisionPos(bCollider, pad2);
                }
                bX -= bVelX;
                bCollider.x = bX;

                bVelX = -bVelX;
                if (p1) {
                    switch (state) {
                        case 1:
                            bVelY = -bIniVel;
                            break;
                        case 2:
                            bVelY = 0;
                            break;
                        case 3:
                            bVelY = bIniVel;
                            break;
                        default:
                            bVelY = -bIniVel;
                            break;
                    } 
                } else if (p2) {
                    switch (state) {
                        case 1:
                            bVelY = -bIniVel;
                            break;
                        case 2:
                            bVelY = 0;
                            break;
                        case 3:
                            bVelY = bIniVel;
                            break;
                        default:
                            bVelY = -bIniVel;
                            break;
                    }
                }
            }

            bY += bVelY;
            bCollider.y = bY;

            if (bY < 0 || (bY + BALL_HEIGHT > SCREEN_HEIGHT)) {
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


        bool isBallInGame () {
            if (bX < 0 || (bX + BALL_WIDTH > SCREEN_WIDTH)) {
                return false;
            } else {
                return true;
            }
        }

        int collisionPos (SDL_Rect ball, SDL_Rect pad) {
            double bTop, bBot;
            double pTop, pBot;

            bTop = ball.y;
            bBot = ball.y + ball.h;

            pTop = pad.y;
            pBot = pad.y + pad.h;

            double padInit = 0;
            double padTop = pad.h / 3;
            double padMid = pad.h *2/3;
            double padBot = pad.h;

            double bRelP = bTop - pTop;

            if (bRelP >= padInit && bRelP <= padTop) {
                return 1;
            } else if (bRelP > padTop && bRelP < padMid) {
                return 2;
            } else if (bRelP >= padMid && bRelP <= padBot) {
                return 3;
            }
        }

        double getVelY () {
            return bVelY;
        }

    private:
        double bX;
        double bY;
        double bVelX;
        double bVelY;
        SDL_Rect bCollider;
};