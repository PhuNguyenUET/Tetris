#include <iostream>
#include <sstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

using std::string;
using std::cout;
using std::endl;

class ScoreBoard {
    private:
        SDL_Texture* scoreTexture = NULL; 
        TTF_Font* font = NULL;

        int width = 40;
        const int HEIGHT = 60;

    public:
        ScoreBoard() {
            TTF_Init();
            font = TTF_OpenFont("Font/Font.ttf", 50);
        }

        void free() {
            if (scoreTexture != NULL) {
                SDL_DestroyTexture(scoreTexture);
                scoreTexture = NULL;
            }
        }

        void loadFromRenderedText (string textureText, SDL_Renderer* &renderer) {
            free();

            SDL_Color textColor = {255, 255, 255, 255};
            SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);

            scoreTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

            SDL_FreeSurface(textSurface);
        }

        void close () {
            TTF_CloseFont(font);
            font = NULL;
        }

        void render (int x, int y, SDL_Renderer* &renderer) {
            SDL_Rect renderQuad = {x, y, width, HEIGHT};
            SDL_RenderCopy (renderer, scoreTexture, NULL, &renderQuad);
        }
        int getWidth () {
            return width;
        }

        void setWidth (int w) {
            width = w;
        }
};