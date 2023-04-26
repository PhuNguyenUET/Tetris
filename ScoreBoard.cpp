#include <iostream>

#include "ScoreBoard.h"

ScoreBoard::ScoreBoard(int scoreWidth, int scoreHeight, int lineWidth, int lineHeight, SDL_Renderer *&renderer)
{
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

void ScoreBoard::free()
{
    if (scoreTexture != NULL)
    {
        SDL_DestroyTexture(scoreTexture);
        scoreTexture = NULL;
    }
}

void ScoreBoard::loadFromRenderedText(string scoreText, string lineText, string highText, SDL_Renderer *&renderer)
{
    free();

    SDL_Color color = {51, 51, 255, 255};
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, scoreText.c_str(), color);

    scoreTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    SDL_FreeSurface(textSurface);

    SDL_Surface *lineSurface = TTF_RenderText_Solid(font, lineText.c_str(), color);

    lineTexture = SDL_CreateTextureFromSurface(renderer, lineSurface);

    SDL_FreeSurface(lineSurface);

    SDL_Surface *highSurface = TTF_RenderText_Solid(font, highText.c_str(), color);

    highTexture = SDL_CreateTextureFromSurface(renderer, highSurface);

    SDL_FreeSurface(highSurface);
}

void ScoreBoard::close()
{
    free();
    TTF_CloseFont(font);
    IMG_Quit();
    font = NULL;
}

void ScoreBoard::render(int x, int y, SDL_Renderer *&renderer)
{
    neonBoard->render(x, y, renderer);
    SDL_Rect scoreQuad = {x + (neonEdge - scoreWidth) / 2, y + lineHeight + 35, scoreWidth, scoreHeight};
    SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreQuad);
    SDL_Rect lineQuad = {x + (neonEdge - lineWidth) / 2, y + 35, lineWidth, lineHeight};
    SDL_RenderCopy(renderer, lineTexture, NULL, &lineQuad);
    SDL_Rect highQuad = {x + (neonEdge - scoreWidth) / 2, y + lineHeight + scoreHeight + 35, scoreWidth, scoreHeight};
    SDL_RenderCopy(renderer, highTexture, NULL, &highQuad);
}
