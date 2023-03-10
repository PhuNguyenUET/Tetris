#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "LTexture.cpp"

using std::cout;
using std::endl;
using std::string;

const int SCREEN_HEIGHT = 777;
const int SCREEN_WIDTH = 777;

void init (SDL_Window* window, SDL_Renderer* renderer) {
    bool success = true;
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        cout << "Error:" << SDL_GetError() << endl;
        success = false;
    } else {
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

        window = SDL_CreateWindow("BlackJack", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        int imgFlags = IMG_INIT_PNG;
        IMG_Init(imgFlags);
    }
}

void loadMedia (LTexture texture, SDL_Renderer* renderer, string path) {
    texture.loadFromFile(path, renderer);
}

void freeTexture(LTexture texture) {
    texture.free();
}

void close (SDL_Renderer* renderer, SDL_Window* window) {
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    SDL_DestroyWindow(window);
    window = NULL;

    IMG_Quit();
    SDL_Quit();
}

int main (int argc, char* args[]) {
    SDL_Window* window;
    SDL_Renderer* renderer;

    LTexture board;

    init(window, renderer);
    loadMedia(board, renderer, "Board.png");

    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while(SDL_PollEvent(&e) != 0) {
            if (e.type = SDL_QUIT) {
                quit = true;
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        board.render(0, 0, renderer);

        SDL_RenderPresent(renderer);
    }

    close(renderer, window);
    return 0;
}