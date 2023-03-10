#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <string>

#include "ScoreNoti.cpp"

using std::string;
using std::cout;
using std::endl;
using std::to_string;

class Bird {
    private:
    const double VERTI_VELOCITY = 0.11;
    const double HORI_VELOCITY = 0.2; 
    const double VERTI_RISE = 40;
    const double ANGLE_CHANGE = 0.08;
    const double HOVERING = 0.007;

    LTexture* bird = NULL;

    public:
    const double GRAVITY = 0.00007;
    double posX;
    double posY;
    double vel;
    double angle = 0;
    bool hasEvent = false;
    bool up = false;

    SDL_Rect bCollider;

    void loadMedia (SDL_Renderer* &renderer) {
        bird = new LTexture(50, 40);
        (bird)->loadFromFile("Graphics/CrappyBird.png", renderer);        
    }

    void render (SDL_Renderer* &renderer) {
        bird->render(posX, posY, renderer, NULL, angle, NULL);   
    }

    void setX (int x) {
        posX = x;
        bCollider.x = x;
    }

    void setY (int y) {
        posY = y;
        bCollider.y = y;
    }

    int getX () {
        return posX;
    }

    int getY () {
        return posY;
    }

    int getHeight () {
        return bird->getHeight();
    }

    int getWidth () {
        return bird -> getWidth();
    }

    void handleEvent (SDL_Event& e, bool &gameStart) {
        if (e.type == SDL_KEYDOWN) {
            if (e.key.keysym.sym == SDLK_SPACE || e.key.keysym.sym == SDLK_UP) {
                gameStart = true;
                vel = -VERTI_VELOCITY;
                hasEvent = true;
            } 
        } else if (e.type == SDL_MOUSEBUTTONDOWN) {
            gameStart = true;
            vel = -VERTI_VELOCITY;
            hasEvent = true;
        }
    }

    void move (bool& gameEnd, bool& hitGround, bool& hitPipe, bool &gameStart) {
        if (!gameStart) {
            if (up) {
                posY -= HOVERING;
            } else {
                posY += HOVERING;
            }
            if (posY <= (SCREEN_HEIGHT - GROUND - bird->getHeight()) / 2 - 7) {
                up = false;
            } else if (posY >= (SCREEN_HEIGHT - GROUND - bird->getHeight()) / 2 + 7) {
                up = true;
            }
            return;
        }
        if (hitPipe) {
            vel = 0.11;
            hitPipe = false;
        }
        posY += vel;
        bCollider.y = posY;
        if ((posY + bird->getHeight() > SCREEN_HEIGHT - GROUND)) {
            posY -= vel;
            bCollider.y = posY;
            hitGround = true;
            gameEnd = true;
        }
        vel += GRAVITY;
        if (!hasEvent) {
            if (!hitGround && vel > 0.08) {
                if (angle < 90) {
                    angle += ANGLE_CHANGE;
                } else {
                    angle = 90;
                }
            }
        }
        if (hasEvent) {
            if (angle > -30) {
                angle -= 0.45;
            } else {
                hasEvent = false;
            }
        }
    } 

    SDL_Rect getCollider () {
        return bCollider;
    }

    Bird (SDL_Renderer* &renderer) {
        vel = 0;
        loadMedia(renderer);
        bCollider.w = bird->getWidth();
        bCollider.h = bird->getHeight();
    }
}; 