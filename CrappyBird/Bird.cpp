#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <string>

#include "LTexture.cpp"

using std::string;
using std::cout;
using std::endl;
using std::to_string;

class Bird {
    private:
    const double GRAVITY = 0.2;
    const double VERTI_VELOCITY = 0.3;
    const double HORI_VELOCITY = 0.2; 

    LTexture* bird = NULL;
    double posX;
    double posY;
    double vel;

    SDL_Rect bCollider;

    public:
    void loadMedia (SDL_Renderer* &renderer) {
        bird = new LTexture();
        (bird)->loadFromFile("Graphics/Bird.png", renderer);        
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

    void handleEvent (SDL_Event& e) {
        if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
            if (e.key.keysym.sym == SDLK_SPACE || e.key.keysym.sym == SDLK_UP) {
                vel += VERTI_VELOCITY;
            } 
        } else if (e.type == SDL_MOUSEBUTTONDOWN) {
            vel += VERTI_VELOCITY;
        }
    }

    void move () {
        posY += vel;
        bCollider.y = posY;
        if ((posY < GROUND) || (posY + bird->getHeight() > SCREEN_HEIGHT)) {
            posY -= vel;
            bCollider.y = posY;
        }
    } 

    Bird (SDL_Renderer* &renderer) {
        vel = 0;
        loadMedia(renderer);
        bCollider.w = bird->getWidth();
        bCollider.h = bird->getHeight();
        }
}; 