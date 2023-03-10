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

const int SCREEN_WIDTH = 500;
const int SCREEN_HEIGHT = 750;
const int GROUND = 144;

class LTexture {
    public:
    LTexture(int width, int height) {
        mTexture = NULL;
        mWidth = width;
        mHeight = height;
    }

    LTexture () {
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }

    ~LTexture() {
        free();
    }

    void loadFromFile (string path, SDL_Renderer* &renderer) {
        free ();

        SDL_Texture* newTexture = NULL;
        SDL_Surface* loadedSurface = IMG_Load(path.c_str());

        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

        if (mWidth == 0) {
            mWidth = loadedSurface -> w;
        }

        if (mHeight == 0) {
            mHeight = loadedSurface -> h;
        }

        SDL_FreeSurface(loadedSurface);
        mTexture = newTexture;
    }

    void free () {
        if (mTexture != NULL) {
            SDL_DestroyTexture(mTexture);
            mTexture = NULL;
        }
    }

    void render (int x, int y, SDL_Renderer* &renderer, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL) {
        SDL_Rect renderQuad = {x, y, mWidth, mHeight};
        SDL_RendererFlip flip = SDL_FLIP_NONE;
        if (clip != NULL) {
            renderQuad.w = clip -> w;
            renderQuad.h = clip -> h;
        }
        SDL_RenderCopyEx(renderer, mTexture, clip, &renderQuad, angle, center, flip);
    }

    int getWidth () {
        return mWidth;
    }

    int getHeight () {
        return mHeight;
    }

    SDL_Texture* getTexture () {
        return mTexture;
    }

    private:
    SDL_Texture* mTexture;

    int mWidth;
    int mHeight;
};