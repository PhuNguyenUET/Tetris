#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <string>

#include "Constants.h"
#include "LTexture.h"

using std::cout;
using std::endl;
using std::string;
using std::to_string;

class ScoreBoard
{
private:
    const int neonEdge = 230;
    LTexture *neonBoard;
    SDL_Texture *scoreTexture = NULL;
    SDL_Texture *lineTexture = NULL;
    SDL_Texture *highTexture = NULL;
    TTF_Font *font = NULL;

    int scoreWidth;
    int scoreHeight;
    int lineWidth;
    int lineHeight;

public:
    ScoreBoard(int scoreWidth, int scoreHeight, int lineWidth, int lineHeight, SDL_Renderer *&renderer);
    void free();
    void loadFromRenderedText(string scoreText, string lineText, string highText, SDL_Renderer *&renderer);
    void close();
    void render(int x, int y, SDL_Renderer *&renderer);
};

#endif