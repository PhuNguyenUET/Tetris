#ifndef ENDGAMENOTI_H
#define ENDGAMENOTI_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <string>

#include "LTexture.h"
#include "Button.h"
#include "Constants.h"

using std::cout;
using std::endl;
using std::string;
using std::to_string;

class EndGameNoti
{
private:
    LTexture *endGame = NULL;
    SDL_Texture *scoreNoti = NULL;
    TTF_Font *font = NULL;

    Button *returnButton = NULL;
    Button *continueButton = NULL;

    int scoreWidth = 250;
    int scoreHeight = 70;

public:
    EndGameNoti(SDL_Renderer *&renderer);
    void free();
    void loadScore(int score, int highScore, SDL_Renderer *&renderer);
    void close();
    void render(int x, int y, SDL_Renderer *&renderer);
    void handleEvent(SDL_Event &e, bool &playNext, bool &turnBack);
    int getWidth();
    int getHeight();
};

#endif