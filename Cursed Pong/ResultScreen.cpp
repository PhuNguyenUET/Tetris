#include <iostream>
#include <sstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

using std::string;
using std::cout;
using std::endl;

class ResultScreen {
    private:
        SDL_Renderer* resScreen = NULL;
        Mix_Music* music = NULL;
        SDL_Texture* res = NULL;
        SDL_Texture* mes = NULL;
        TTF_Font* font = NULL;
        string result;
        string message = "Press any key or click the mouse to continue.";

        SDL_Texture* loadFromRenderedText (string textureText, SDL_Renderer* &renderer) {
            //free();
            SDL_Texture* texture = NULL;

            SDL_Color textColor = {255, 255, 255, 255};
            SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);

            texture = SDL_CreateTextureFromSurface(renderer, textSurface);

            SDL_FreeSurface(textSurface);

            return texture;
        }

    public:
        void init (SDL_Window*& titleWindow, bool& win) {
            SDL_Init(SDL_INIT_EVERYTHING);
            SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

            resScreen = SDL_CreateRenderer(titleWindow, -1, SDL_RENDERER_ACCELERATED);

            SDL_SetRenderDrawColor (resScreen, 0, 0, 0, 255);

            Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

            if (win) {
                music = Mix_LoadMUS("Audio/Clapping.wav");
                Mix_PlayMusic(music, 0);
                result = "You Win";
            } else {
                music = Mix_LoadMUS("Audio/Harry.wav");
                Mix_PlayMusic(music, 0);
                result = "You Lost";
            }

            TTF_Init();
            font = TTF_OpenFont("Font/Oswald.ttf", 50);
        }

        void close () {
            Mix_FreeMusic(music);
            music = NULL;

            SDL_DestroyRenderer(resScreen);
            resScreen = NULL;

            SDL_DestroyTexture(res);
            SDL_DestroyTexture(mes);
            res = NULL;
            mes = NULL;

            Mix_Quit();
            TTF_Quit();
        }

        void render (int x, int y, int w, int h, SDL_Texture*& texture, SDL_Renderer* &renderer) {
            SDL_Rect renderQuad = {x, y, w, h};
            SDL_RenderCopy (renderer, texture, NULL, &renderQuad);
        }

        ResultScreen (SDL_Window* window, bool& win, bool& con) {
            init(window, win);

            res = loadFromRenderedText(result, resScreen);

            font = TTF_OpenFont("Font/Oswald.ttf", 30);
            mes = loadFromRenderedText(message, resScreen);

            bool quit = false;
            SDL_Event e;

            while (!quit) {
                con = false;
                while (SDL_PollEvent(&e)) {
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    } else {
                        if (e.type == SDL_KEYDOWN || e.type == SDL_MOUSEBUTTONDOWN) {
                            con = true;
                        }
                    }
                }
                SDL_SetRenderDrawColor(resScreen, 0, 0, 0, 255);
                SDL_RenderClear(resScreen);

                render (160, 50, 500, 60, res, resScreen);
                render (110, 150, 600, 60, mes, resScreen);

                SDL_RenderPresent(resScreen);
                if (con == true) {
                    break;
                }
            }

            close ();
            if (quit) {
                SDL_DestroyWindow(window);
                SDL_Quit();
            }
        }
};