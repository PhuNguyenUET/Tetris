#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <string>

#include "Bird.cpp";

using std::string;
using std::cout;
using std::endl;
using std::to_string;

class Pillar {
    private:
    const int OPEN_WIDTH = 30;
    const int PLAYSPACE = SCREEN_HEIGHT - GROUND;
    //const int OPEN_HEIGHT = 120;
    const int OPEN_HEIGHT = 150;
    const double HORI_VEL = 0.035;

    int openY;
    double vel;
    double posX;

    SDL_Rect upCollider;
    SDL_Rect downCollider;

    LTexture* upPillar = NULL;
    LTexture* downPillar = NULL;

    public:
    void loadMedia (SDL_Renderer* &renderer) {
        upPillar = new LTexture();
        downPillar = new LTexture();
        upPillar->loadFromFile("Graphics/upPipe.png", renderer);
        downPillar->loadFromFile("Graphics/downPipe.png", renderer);
    }

    void render (SDL_Renderer* &renderer) {
        SDL_Rect upperClip = {0, upPillar -> getHeight() - openY, upPillar -> getWidth(), openY};
        upPillar->render(posX, 0, renderer, &upperClip);

        double lowerHeight = PLAYSPACE - openY - OPEN_HEIGHT;
        SDL_Rect lowerClip = {0, 0, downPillar -> getWidth(), lowerHeight};
        downPillar -> render (posX, openY + OPEN_HEIGHT, renderer, &lowerClip);
    }

    void move (bool gameEnd) {
        posX -= HORI_VEL;
        upCollider.x = posX;
        downCollider.x = posX;
        
        if (gameEnd) {
            posX += HORI_VEL;
            upCollider.x = posX;
            downCollider.x = posX;
        }
    }

    void handleCollision (bool& gameEnd, Bird* &bird) {
        if (checkCollision(bird->getCollider(), upCollider) || checkCollision(bird->getCollider(), downCollider)) {
            gameEnd = true;
        }
        /*if (bird -> posY <= upCollider.y + upCollider.h && (bird -> posX + bird->getWidth()>= upCollider.x)) {
            vel -= bird -> GRAVITY;
            bird -> posY -= vel;
            bird -> bCollider.y = bird -> posY;
            gameEnd = true;
            bird -> vel = 0;
        } */
    }

    bool checkCollision (SDL_Rect bird, SDL_Rect pillar) {
        int bLeft, bRight;
        int pLeft, pRight;
        int bTop, bBot;
        int pTop, pBot;

        bLeft = bird.x;
        bRight = bird.x + bird.w;
        bTop = bird.y;
        bBot = bird.y + bird.h;

        pLeft = pillar.x;
        pRight = pillar.x + pillar.w;
        pTop = pillar.y;
        pBot = pillar.y + pillar.h;

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

    int getPosX () {
        return posX;
    }

    SDL_Rect getUpCollider () {
        return upCollider;
    }

    int getWidth () {
        return upPillar -> getWidth();
    }

    Pillar (SDL_Renderer* &renderer) {
        posX = SCREEN_WIDTH;
        openY = rand() % (PLAYSPACE - 300) + 100;
        loadMedia(renderer);
        upCollider.w = upPillar -> getWidth();
        upCollider.h = openY;
        upCollider.x = posX;
        upCollider.y = 0;
    
        downCollider.w = downPillar -> getWidth();
        downCollider.h = PLAYSPACE - openY - OPEN_HEIGHT;
        downCollider.x = posX;
        downCollider.y = openY + OPEN_HEIGHT;
    }
};