#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <string>

#include "Window.cpp"

using std::string;
using std::cout;
using std::endl;
using std::to_string;

class TitleScreen {
    private:
        SDL_Renderer* renderer;
        Button* playBut;
        Button* settingBut;
        LTexture* backGround;
        LTexture* introFont;
        SettingScreen* settingScreen;
        Mix_Music *titleMusic = NULL;


    public:
        void init (SDL_Window* &window, bool firstTime) {
            if (firstTime) {
                SDL_Init (SDL_INIT_EVERYTHING);
                SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

                window = SDL_CreateWindow("Tetris for the Depressed", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
            }
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

            SDL_SetRenderDrawColor (renderer, 0, 0, 0, 255);
            int imgFlag = IMG_INIT_PNG;
            IMG_Init(imgFlag);

            Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
        }

        void loadMedia () {
            backGround->loadFromFile("Graphics/Starting_screen.png", renderer);
            introFont->loadFromFile("Graphics/Logo.png", renderer);

            titleMusic = Mix_LoadMUS("Audio/TitleMusic.wav");
        }

        void close () {
            SDL_DestroyRenderer(renderer);
            renderer = NULL;

            Mix_FreeMusic(titleMusic);
            titleMusic = NULL;

            Mix_Quit();
            IMG_Quit();
        }

        void kill (SDL_Window* &window) {
            SDL_DestroyWindow(window);
            window = NULL;
            SDL_Quit();
        }

        TitleScreen (SDL_Window* &window, bool &quit, bool firstTime, double& systemVolume, double& musicVolume, int& songIdx) {
            init (window, firstTime);

            playBut = new Button(renderer, "Graphics/PlayButton3.png", 333, 250);
            settingBut = new Button(renderer, "Graphics/SettingsButton.png", 70, 70);
            backGround = new LTexture(SCREEN_WIDTH, SCREEN_HEIGHT);
            introFont = new LTexture(450, 150);

            loadMedia();

            playBut->setPos((SCREEN_WIDTH - 333) / 2, 220);
            settingBut->setPos(0, 0);

            bool change = false;
            bool openSetting = false;
            SDL_Event e;

            Mix_PlayMusic(titleMusic, 0);

            settingScreen = new SettingScreen(renderer, 110, 0, systemVolume, musicVolume, songIdx);

            while (!quit && !change) {
                if (!openSetting) {
                    while (SDL_PollEvent(&e) != 0) {
                        if (e.type == SDL_QUIT) {
                            quit = true;
                        } else {
                            playBut->handleEvent(e, change);
                            settingBut->handleEvent(e, openSetting);
                        }
                    } 
                } else {
                    while (SDL_PollEvent(&e) != 0) {
                        if (e.type == SDL_QUIT) {
                            quit = true;
                            break;
                        } else {
                            settingScreen->handleEvent(renderer, e, openSetting, systemVolume, musicVolume, songIdx);
                        }
                    } 
                }
                Mix_VolumeMusic(MIX_MAX_VOLUME * musicVolume);

                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderClear(renderer);

                backGround->render(0, 0, renderer);
                introFont->render((SCREEN_WIDTH - 450) / 2, 50, renderer);
                playBut->render(renderer);
                settingBut->render(renderer);

                if (openSetting) {
                    settingScreen->render(renderer, songIdx);
                }

                SDL_RenderPresent(renderer);
            }
            playBut->close();
            settingBut->close();
            if (quit) {
                close();
                kill(window);
            } else {
                close();
            }
        }
};