#include <iostream>
#include <sstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

using std::string;
using std::cout;
using std::endl;

    const int SCREEN_WIDTH_B = 800;
    const int SCREEN_HEIGHT_B = 600;

class Button {
    private:
        const int BUTTON_WIDTH = 200;
        const int BUTTON_HEIGHT = 200;
        SDL_Texture* buttonGraphics;
        Mix_Chunk* butHit = NULL;
        SDL_Point position;
    public:
        Button (SDL_Renderer* renderer) {
            position.x = 300;
            position.y = 170;
            string path = "Graphics/PlayButton3.png";
            SDL_Surface* loadedSurface = IMG_Load (path.c_str());
            buttonGraphics = SDL_CreateTextureFromSurface(renderer, loadedSurface);
            SDL_FreeSurface(loadedSurface);

            Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

            butHit = Mix_LoadWAV("Audio/Button_hit.wav");

        }

        void setPosition (int x, int y) {
            position.x = x;
            position.y = y;
        }

        void handleEvent (SDL_Event* const &e, bool& quit) {
            if (e -> type == SDL_MOUSEBUTTONDOWN) {
                int x,y;
                SDL_GetMouseState(&x, &y);

                bool inside = true;

                if (x < position.x) {
                    inside = false;
                } else if (x > position.x + BUTTON_WIDTH) {
                    inside = false;
                } else if (y < position.y) {
                    inside = false;
                } else if (y > position.y +BUTTON_HEIGHT) {
                    inside = false;
                }

                if (inside) {
                    Mix_PlayChannel(-1, butHit, 0);
                    quit = true;
                }
            }
        }

        void render (SDL_Renderer* &renderer) {
            SDL_Rect renderQuad = {position.x, position.y, BUTTON_WIDTH, BUTTON_HEIGHT};
            SDL_RenderCopy(renderer, buttonGraphics, NULL, &renderQuad);
        }
        
        void close () {
            SDL_DestroyTexture(buttonGraphics);
            buttonGraphics = NULL;
        }
};