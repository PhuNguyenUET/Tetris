#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <string>

#include "LTexture.cpp";

using std::string;
using std::cout;
using std::endl;
using std::to_string;

class EndGameNoti {
    private:
        LTexture* endGame = NULL;   
        SDL_Texture* noti = NULL;
        TTF_Font* font = NULL;

        int width = 300;
        int height = 70;

    public:
        EndGameNoti (SDL_Renderer* &renderer) {
            TTF_Init();
            font = TTF_OpenFont("Font/Font.ttf", 30);

            int imgFlag = IMG_INIT_PNG;
            IMG_Init(imgFlag);

            endGame = new LTexture(300, 170);

            endGame->loadFromFile("Graphics/GameOver.png", renderer);

            this->loadFromRenderedText(renderer);
        }

        void free () {
            if (noti != NULL) {
                SDL_DestroyTexture(noti);
                noti = NULL;
            }
        }

        void loadFromRenderedText (SDL_Renderer* &renderer) {
            free();

            string text = "Press any key to continue";

            SDL_Color textColor = {0, 0, 0, 255};
            SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);

            noti = SDL_CreateTextureFromSurface(renderer, textSurface);

            SDL_FreeSurface(textSurface);
        }

        void close () {
            free(); 
            
            TTF_CloseFont(font);
            font = NULL;
        }

        void render (int x, int y, SDL_Renderer* &renderer) {
            endGame->render(x, y, renderer);
            SDL_Rect scoreRenderQuad = {x + endGame->getWidth() / 2 - width / 2, y + 110, width, height};
            SDL_RenderCopy(renderer, noti, NULL, &scoreRenderQuad);
        } 
        
        void handleEvent (SDL_Event& e, bool &playNext) {
            if (e.type == SDL_KEYDOWN) {
                if (playNext == false) {
                    playNext = true;
                }
            }
        }
        int getWidth () {
            return endGame->getWidth();
        }
        int getHeight () {
            return endGame->getHeight();
        }
};