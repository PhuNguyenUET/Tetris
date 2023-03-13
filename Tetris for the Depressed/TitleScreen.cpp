#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <string>

#include "Window.cpp"
#include "Button.cpp"

using std::string;
using std::cout;
using std::endl;
using std::to_string;

class TitleScreen {
    private:
        SDL_Renderer* renderer;
        Button* but;
        LTexture* backGround;
        LTexture* introFont;


    public:
        void init (SDL_Window* &window) {
            SDL_Init (SDL_INIT_EVERYTHING);
            SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

            window = SDL_CreateWindow("Tetris for the Depressed", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

            SDL_SetRenderDrawColor (renderer, 0, 0, 0, 255);
            int imgFlag = IMG_INIT_PNG;
            IMG_Init(imgFlag);
        }

        void loadMedia () {
            backGround->loadFromFile("Graphics/WaitBackground.png", renderer);
            introFont->loadFromFile("Graphics/Logo.png", renderer);
        }

        void close () {
            SDL_DestroyRenderer(renderer);
            renderer = NULL;

            IMG_Quit();
        }

        void kill (SDL_Window* &window) {
            SDL_DestroyWindow(window);
            window = NULL;
            SDL_Quit();
        }

        TitleScreen (SDL_Window* &window, bool &quit) {
            init (window);

            but = new Button(renderer);
            backGround = new LTexture(SCREEN_WIDTH, SCREEN_HEIGHT);
            introFont = new LTexture(350, 170);

            loadMedia();

            but->setPos(100, 350);

            bool change = false;
            SDL_Event e;

            while (!quit && !change) {
                while (SDL_PollEvent(&e) != 0) {
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    } else {
                        but->handleEvent(e, change);
                    }
                } 

                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderClear(renderer);

                backGround->render(0, 0, renderer);
                introFont->render((SCREEN_WIDTH - 350) / 2, 50, renderer);
                but->render(renderer);

                SDL_RenderPresent(renderer);
            }
            but->close();
            if (quit) {
                close();
                kill(window);
            } else {
                close();
            }
        }
};