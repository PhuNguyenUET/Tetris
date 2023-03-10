#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <string>

#include "Pillar.cpp"

using std::string;
using std::cout;
using std::endl;
using std::to_string;

class Bird {
    private:
    const double GRAVITY = 0.00006;
    const double VERTI_VELOCITY = 0.08;
    const double HORI_VELOCITY = 0.2; 
    const double VERTI_RISE = 40;

    LTexture* bird = NULL;
    double posX;
    double posY;
    double vel;

    SDL_Rect bCollider;

    public:
    void loadMedia (SDL_Renderer* &renderer) {
        bird = new LTexture(50, 40);
        (bird)->loadFromFile("Graphics/CrappyBird.png", renderer);        
    }

    void render (SDL_Renderer* &renderer) {
        bird->render(posX, posY, renderer);   
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

    void handleEvent (SDL_Event& e) {
        if (e.type == SDL_KEYDOWN) {
            if (e.key.keysym.sym == SDLK_SPACE || e.key.keysym.sym == SDLK_UP) {
                vel = -VERTI_VELOCITY;
            } 
        } else if (e.type == SDL_MOUSEBUTTONDOWN) {
            vel = -VERTI_VELOCITY;
        }
    }

    void move (Pillar* &pillar, bool& gameEnd) {
        posY += vel;
        bCollider.y = posY;
        if ((posY + bird->getHeight() > SCREEN_HEIGHT - GROUND)) {
            posY -= vel;
            bCollider.y = posY;
        }
        SDL_Rect upCollider = pillar->getUpCollider();
        if (posY <= upCollider.y + upCollider.h && (posX >= upCollider.x)) {
            posY -= vel;
            bCollider.y = posY;
            gameEnd = true;
            vel = 0;
        }
        vel += GRAVITY;
    } 

    void handleCollision (bool& gameEnd, Pillar* &pillar) {
        if (checkCollision(bCollider, pillar -> getUpCollider()) || checkCollision(bCollider, pillar -> getDownCollider())) {
            gameEnd = true;
        }
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

    Bird (SDL_Renderer* &renderer) {
        vel = 0;
        loadMedia(renderer);
        bCollider.w = bird->getWidth();
        bCollider.h = bird->getHeight();
        }
}; 