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
    const double VERTI_VELOCITY = 0.1;
    const double HORI_VELOCITY = 0.2; 
    const double VERTI_RISE = 40;

    LTexture* bird = NULL;

    public:
    const double GRAVITY = 0.00009;
    double posX;
    double posY;
    double vel;

    SDL_Rect bCollider;

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

    void move () {
        posY += vel;
        bCollider.y = posY;
        if ((posY + bird->getHeight() > SCREEN_HEIGHT - GROUND)) {
            posY -= vel;
            bCollider.y = posY;
        }
        vel += GRAVITY;
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