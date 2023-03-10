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
        TTF_Font* font = NULL;
        Mix_Chunk* buttonHit = NULL;
        Button* playButton;
        SDL_Texture* title = NULL;
        SDL_Texture* recommend1 = NULL;
        SDL_Texture* recommend2 = NULL;
        string tit = "Cursed Pong";
        string re1 = "Headphones are NOT recommended!";
        string re2 = "Please turn down the volume.";


        SDL_Texture* loadFromRenderedText (string textureText, SDL_Renderer* &renderer) {
            //free();
            SDL_Texture* texture = NULL;

            SDL_Color textColor = {255, 255, 255, 255};
            SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);

            texture = SDL_CreateTextureFromSurface(renderer, textSurface);

            SDL_FreeSurface(textSurface);

            return texture;
        }

        void free () {
            if (title != NULL) {
                SDL_DestroyTexture(title);
                title = NULL;
            }
        }

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
            font = TTF_OpenFont("Font/Oswald.ttf", 50);
        }

        void close () {
            Mix_FreeMusic(music);
            music = NULL;

            SDL_DestroyRenderer(titleRenderer);
            titleRenderer = NULL;

            SDL_DestroyTexture(title);
            SDL_DestroyTexture(recommend1);
            SDL_DestroyTexture(recommend2);
            title = NULL;
            recommend1 = NULL;
            recommend2 = NULL;

            IMG_Quit();
            Mix_Quit();
            TTF_Quit();
        }

        void render (int x, int y, int w, int h, SDL_Texture*& texture, SDL_Renderer* &renderer) {
            SDL_Rect renderQuad = {x, y, w, h};
            SDL_RenderCopy (renderer, texture, NULL, &renderQuad);
        }

        TitleScreen (SDL_Window* &window, bool& shutDown) {
            init(window);
                
            font = TTF_OpenFont("Font/Oswald.ttf", 50);
            title = loadFromRenderedText(tit, titleRenderer);

            font = TTF_OpenFont("Font/Oswald.ttf", 30);
            recommend1 = loadFromRenderedText(re1, titleRenderer);

            recommend2 = loadFromRenderedText(re2, titleRenderer);

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
                render (160, 50, 500, 100, title, titleRenderer);
                render (110, 500, 600, 60, recommend1, titleRenderer);
                render (110, 400, 600, 60, recommend2, titleRenderer);

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