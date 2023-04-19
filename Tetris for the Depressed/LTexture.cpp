#include <iostream>

#include "LTexture.h"

    LTexture::LTexture(int width, int height) {
        mTexture = NULL;
        mWidth = width;
        mHeight = height;
    }

    LTexture::LTexture () {
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }

    LTexture::~LTexture() {
        free();
    }

    void LTexture::loadFromFile (string path, SDL_Renderer* &renderer) {
        free ();

        SDL_Texture* newTexture = NULL;
        SDL_Surface* loadedSurface = IMG_Load(path.c_str());

        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

        orgiHeight = loadedSurface->h;
        orgiWidth = loadedSurface->w;

        if (mWidth == 0) {
            mWidth = loadedSurface -> w;
        }

        if (mHeight == 0) {
            mHeight = loadedSurface -> h;
        }

        SDL_FreeSurface(loadedSurface);
        mTexture = newTexture;
    }

    void LTexture::free () {
        if (mTexture != NULL) {
            SDL_DestroyTexture(mTexture);
            mTexture = NULL;
        }
    }

    void LTexture::render (int x, int y, SDL_Renderer* &renderer, SDL_Rect* clip, double angle, SDL_Point* center) {
        SDL_Rect renderQuad = {x, y, mWidth, mHeight};
        SDL_RendererFlip flip = SDL_FLIP_NONE;
        if (clip != NULL) {
            renderQuad.w = mWidth * (double)clip -> w / (double)orgiWidth;
            renderQuad.h = mHeight * (double)clip -> h / (double)orgiHeight;
        }
        SDL_RenderCopyEx(renderer, mTexture, clip, &renderQuad, angle, center, flip);
    }

    int LTexture::getWidth () {
        return mWidth;
    }

    int LTexture::getHeight () {
        return mHeight;
    }

    SDL_Texture* LTexture::getTexture () {
        return mTexture;
    }
