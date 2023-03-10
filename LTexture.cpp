#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using std::cout;
using std::string;
using std::endl;
class LTexture {
    public: 
    LTexture() {
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }

    ~LTexture() {
        free();
    }

    bool loadFromFile(string path, SDL_Renderer* renderer) {
        free();
        SDL_Texture* newTexture = NULL;

        SDL_Surface* loadedSurface = IMG_Load(path.c_str());
        if (loadedSurface == NULL) {
            cout << "Unable to load image. Error:" << IMG_GetError() << endl;
        } else {
            newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        }
        
        if (newTexture == NULL) {
            cout << "Unable to create texture. Error:" << IMG_GetError() << endl;
        } else {
            mWidth = loadedSurface -> w;
            mHeight = loadedSurface -> h;
        }

        SDL_FreeSurface(loadedSurface);

        mTexture = newTexture;
        return mTexture != NULL;
    }

    void free () {
        if (mTexture != NULL) {
            SDL_DestroyTexture(mTexture);
            mTexture = NULL;
            mWidth = 0;
            mHeight = 0;
        }
    }

    void render (int x, int y, SDL_Renderer* renderer) {
        SDL_Rect renderQuad = {x,y,mWidth,mHeight};
        SDL_RenderCopy(renderer, mTexture, NULL, NULL);
    }

    int getWidth () {
        return mWidth;
    }

    int getHeight () {
        return mHeight;
    }

    private:
    SDL_Texture* mTexture;
    int mWidth;
    int mHeight;
};