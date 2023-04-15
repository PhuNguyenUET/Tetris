#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <string>

#include "ScoreBoard.cpp"

using std::string;
using std::cout;
using std::endl;
using std::to_string;

class EndGameNoti {
    private:
        LTexture* endGame = NULL;   
        SDL_Texture* scoreNoti = NULL;
        TTF_Font* font = NULL;

        Button* returnButton = NULL;
        Button* continueButton = NULL;
        
        int scoreWidth = 250;
        int scoreHeight = 70;

    public:
        EndGameNoti (SDL_Renderer* &renderer) {
            TTF_Init();
            font = TTF_OpenFont("Font/Font.ttf", 30);

            int imgFlag = IMG_INIT_PNG;
            IMG_Init(imgFlag);

            endGame = new LTexture(300, 170);

            endGame->loadFromFile("Graphics/GameOver.png", renderer);

            returnButton = new Button(renderer, "Graphics/ReturnButton.png", 200, 75);
            returnButton->setPos((SCREEN_WIDTH - 200) / 2, 450);

            continueButton = new Button(renderer, "Graphics/ContinueButton.png", 225, 75);
            continueButton->setPos((SCREEN_WIDTH - 225) / 2, 350);
        }

        void free () {
            if (scoreNoti != NULL) {
                SDL_DestroyTexture(scoreNoti);
                scoreNoti = NULL;
            }
        }

        void loadScore (int score, int highScore, SDL_Renderer* &renderer) {
            if (scoreNoti != NULL) {
                SDL_DestroyTexture(scoreNoti);
                scoreNoti = NULL;
            }

            string text;
            if (score < highScore) {
                text = "You scored: " + to_string(score);
            } else {
                text = "You got a new record!";
            }

            SDL_Color textColor = {255, 255, 255, 255};
            SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);

            scoreNoti = SDL_CreateTextureFromSurface(renderer, textSurface);

            SDL_FreeSurface(textSurface);
        }

        void close () {
            free(); 
            
            TTF_CloseFont(font);
            font = NULL;
        }

        void render (int x, int y, SDL_Renderer* &renderer) {
            endGame->render(x, y, renderer);
            SDL_Rect scoreRenderQuad = {x + endGame->getWidth() / 2 - scoreWidth / 2, y + 110, scoreWidth, scoreHeight};
            SDL_RenderCopy(renderer, scoreNoti, NULL, &scoreRenderQuad);
            returnButton->render(renderer);
            continueButton->render(renderer);
        } 
        
        void handleEvent (SDL_Event& e, bool &playNext, bool& turnBack) {
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                returnButton->handleEvent(e, turnBack);
                continueButton->handleEvent(e, playNext);
            }
        }
        int getWidth () {
            return endGame->getWidth();
        }
        int getHeight () {
            return endGame->getHeight();
        }
};