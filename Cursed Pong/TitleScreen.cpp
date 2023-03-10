#include <iostream>
#include <sstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include "Button.cpp"

using std::string;
using std::cout;
using std::endl;

class TitleScreen {
    private:
        SDL_Renderer* titleRenderer;
        Mix_Music* music = NULL;
        Mix_Chunk* buttonHit = NULL;
        Button* playButton;
        SDL_Texture* title;
        SDL_Texture* recommend;

    public: 
        void init (SDL_Window*& titleWindow) {
            SDL_Init(SDL_INIT_EVERYTHING);
            SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

            titleWindow = SDL_CreateWindow("Cursed Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH_B, SCREEN_HEIGHT_B, SDL_WINDOW_SHOWN);
            titleRenderer = SDL_CreateRenderer(titleWindow, -1, SDL_RENDERER_ACCELERATED);

            SDL_SetRenderDrawColor (titleRenderer, 0, 0, 0, 255);
            int imgFlag = IMG_INIT_PNG;
            IMG_Init(imgFlag);

            Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

            music = Mix_LoadMUS("Audio/Intro2.wav");
            Mix_PlayMusic(music, 0);

            TTF_Init();
        }

        void close () {
            Mix_FreeMusic(music);
            music = NULL;

            SDL_DestroyRenderer(titleRenderer);
            titleRenderer = NULL;

            IMG_Quit();
            Mix_Quit();
            TTF_Quit();
        }

        TitleScreen (SDL_Window* &window, bool& shutDown) {
            init(window);

            playButton = new Button(titleRenderer);

            bool quit = false;
            SDL_Event e;

            while (!quit && !shutDown) {
                while (SDL_PollEvent(&e)) {
                    if (e.type == SDL_QUIT) {
                        shutDown = true;
                    } else {
                        playButton->handleEvent(&e, quit);
                    }
                }

                SDL_SetRenderDrawColor(titleRenderer, 0, 0, 0, 255);
                SDL_RenderClear(titleRenderer);

                playButton->render(titleRenderer);

                SDL_RenderPresent(titleRenderer);
            }
            if (!shutDown) {
                playButton->close();
                close();
            } else {
                SDL_DestroyWindow(window);
                window = NULL;
                SDL_Quit();
            }
        }

};