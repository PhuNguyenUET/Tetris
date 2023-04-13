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

class ScoreBoard {
    private:
        const int neonEdge = 230;
        LTexture* neonBoard;
        SDL_Texture* scoreTexture = NULL;
        SDL_Texture* lineTexture = NULL;
        TTF_Font* font = NULL;

        int scoreWidth;
        int scoreHeight;
        int lineWidth;
        int lineHeight;

    public:
        ScoreBoard (int scoreWidth, int scoreHeight, int lineWidth, int lineHeight, SDL_Renderer* &renderer) {
            int imgFlag = IMG_INIT_PNG;
            IMG_Init(imgFlag);
            TTF_Init();
            font = TTF_OpenFont("Font/Font.ttf", 30);
            neonBoard = new LTexture(neonEdge, neonEdge);
            neonBoard->loadFromFile("Graphics/Neon_square.png", renderer);
            this->scoreWidth = scoreWidth;
            this->scoreHeight = scoreHeight;
            this->lineWidth = lineWidth;
            this->lineHeight = lineHeight;
        }

        void free () {
            if (scoreTexture != NULL) {
                SDL_DestroyTexture(scoreTexture);
                scoreTexture = NULL;
            }
        }

        void loadFromRenderedText (string scoreText, string lineText, SDL_Renderer* &renderer) {
            free ();

            SDL_Color color = {51, 51, 255, 255};
            SDL_Surface* textSurface = TTF_RenderText_Solid(font, scoreText.c_str(), color);

            scoreTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

            SDL_FreeSurface(textSurface);

            SDL_Surface* lineSurface = TTF_RenderText_Solid(font, lineText.c_str(), color);

            lineTexture = SDL_CreateTextureFromSurface(renderer, lineSurface);

            SDL_FreeSurface(lineSurface);
        }

        void close () {
            free();
            TTF_CloseFont(font);
            IMG_Quit();
            font = NULL; 
        }

        void render (int x, int y, SDL_Renderer* &renderer) {
            neonBoard->render(x, y, renderer);
            SDL_Rect scoreQuad = {x + (neonEdge - scoreWidth)/2, y + lineHeight + 50, scoreWidth, scoreHeight};
            SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreQuad);
            SDL_Rect lineQuad = {x + (neonEdge - lineWidth)/2, y + 50, lineWidth, lineHeight};
            SDL_RenderCopy(renderer, lineTexture, NULL, &lineQuad);
        }
};