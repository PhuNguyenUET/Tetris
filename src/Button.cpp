#include <iostream>

#include "../Header/Button.h"

Button::Button(SDL_Renderer *&renderer, string path, int width, int height)
{
    ;
    SDL_Surface *buttonSurface = IMG_Load(path.c_str());
    buttonTexture = SDL_CreateTextureFromSurface(renderer, buttonSurface);
    SDL_FreeSurface(buttonSurface);
    this->width = width;
    this->height = height;
}

void Button::setPos(int x, int y)
{
    pos.x = x;
    pos.y = y;
}

void Button::handleEvent(SDL_Event &e, bool &change)
{
    if (e.type == SDL_MOUSEBUTTONDOWN)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);

        bool inside = true;

        if (x < pos.x)
        {
            inside = false;
        }
        if (x > pos.x + width)
        {
            inside = false;
        }
        if (y < pos.y)
        {
            inside = false;
        }
        if (y > pos.y + height)
        {
            inside = false;
        }

        if (inside)
        {
            change = true;
        }
    }
}

void Button::render(SDL_Renderer *&renderer)
{
    SDL_Rect renderQuad = {pos.x, pos.y, width, height};
    SDL_RenderCopy(renderer, buttonTexture, NULL, &renderQuad);
}

void Button::close()
{
    SDL_DestroyTexture(buttonTexture);
    buttonTexture = NULL;
}