#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <string>

using std::string;
using std::cout;
using std::endl;
using std::to_string;

class ScoreBoard {
    private:
        SDL_Texture* scoreTexture = NULL;
        TTF_Font* font = NULL;

        int width;
        int height;

    public:
        ScoreBoard (int width, int height) {
            TTF_Init();
            font = TTF_OpenFont("Font/Font.ttf", 30);
            this->width = width;
            this->height = height;
        }

        void free () {
            if (scoreTexture != NULL) {
                SDL_DestroyTexture(scoreTexture);
                scoreTexture = NULL;
            }
        }

        void loadFromRenderedText (string text, SDL_Renderer* &renderer) {
            free ();

            SDL_Color color = {0, 0, 0, 255};
            SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);

            scoreTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

            SDL_FreeSurface(textSurface);
        }

        void close () {
            free();
            TTF_CloseFont(font);
            font = NULL; 
        }

        void render (int x, int y, SDL_Renderer* &renderer) {
            SDL_Rect renderQuad = {x, y, width, height};
            SDL_RenderCopy(renderer, scoreTexture, NULL, &renderQuad);
        }
};