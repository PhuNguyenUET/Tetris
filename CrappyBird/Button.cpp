#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <string>

// #include "LTexture.cpp"

const int SCREEN_WIDTH_B = 500;
const int SCREEN_HEIGHT_B = 750;

using std::string;
using std::cout;
using std::endl;
using std::to_string;

class Button {
    private:
        const int BUTTON_WIDTH = 300;
        const int BUTTON_HEIGHT = 130;
        SDL_Texture* buttonGraphics;
        SDL_Point pos;
    public:
        Button (SDL_Renderer* &renderer) {
            string path = "Graphics/PlayButton2.png";
            SDL_Surface* loadedSurface = IMG_Load(path.c_str());
            buttonGraphics = SDL_CreateTextureFromSurface(renderer, loadedSurface);
            SDL_FreeSurface(loadedSurface);
        }

        void setPos (int x, int y) {
            pos.x = x;
            pos.y = y;
        }

        void handleEvent (SDL_Event &e, bool &change) {
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                int x,y;
                SDL_GetMouseState(&x, &y);

                bool inside = true;

                if (x < pos.x) {
                    inside = false;
                } 
                if (x > pos.x + BUTTON_WIDTH) {
                    inside = false;
                }
                if (y < pos.y) {
                    inside = false;
                }
                if (y > pos.y + BUTTON_HEIGHT) {
                    inside = false;
                }

                if (inside) {
                    change = true;
                }
            }
        }

        void render (SDL_Renderer* &renderer) {
            SDL_Rect renderQuad = {pos.x, pos.y, BUTTON_WIDTH, BUTTON_HEIGHT};
            SDL_RenderCopy(renderer, buttonGraphics, NULL, &renderQuad);
        }

        void close () {
            SDL_DestroyTexture(buttonGraphics);
            buttonGraphics = NULL;
        }
};