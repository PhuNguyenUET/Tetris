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

class ScoreNoti {
    private:
        LTexture* scoreBackGround;
        SDL_Texture* scoreTexture = NULL;
        TTF_Font* font = NULL;

        int width = 60;
        int height = 90;

    public:
        ScoreNoti(SDL_Renderer* renderer) {
            TTF_Init();
            font = TTF_OpenFont("Text/Font.ttf", 50);

            int imgFlag = IMG_INIT_PNG;
            IMG_Init(imgFlag);

            scoreBackGround = new LTexture(300, 170);
            scoreBackGround->loadFromFile("Graphics/ScoreBackGround.png", renderer);
        }

        void free () {
            if (scoreTexture != NULL) {
                SDL_DestroyTexture(scoreTexture);
                scoreTexture = NULL;
            }
        }

        void loadFromRenderedText (string text, SDL_Renderer* &renderer) {
            free();

            SDL_Color textColor = {255, 255, 255, 255};
            SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);

            scoreTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

            SDL_FreeSurface(textSurface);
        }

        void close () {
            TTF_CloseFont(font);
            font = NULL;
        }

        void render (int x, int y, SDL_Renderer* &renderer) {
            scoreBackGround->render(x, y, renderer);
            SDL_Rect scoreRenderQuad = {x + (scoreBackGround->getWidth() - width)/2, y + (scoreBackGround->getHeight() - height) / 2, width, height};
            SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRenderQuad);
        } 
        
        void handleEvent (SDL_Event& e, bool &playNext) {
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_UP || e.key.keysym.sym == SDLK_SPACE) {
                    if (playNext == false) {
                        playNext = true;
                    }
                }
            } else if (e.type == SDL_MOUSEBUTTONDOWN) {
                if (playNext == false) {
                    playNext = true;
                }
            }
        }
        int getWidth () {
            return scoreBackGround->getWidth();
        }
        int getHeight () {
            return scoreBackGround->getHeight();
        }
};