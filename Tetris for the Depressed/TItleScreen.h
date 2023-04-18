#ifndef TITLESCREEN_H
#define TITLESCREEN_H

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
        void init (SDL_Window* &window, bool firstTime);
        void loadMedia ();
        void close ();
        void kill (SDL_Window* &window);
        TitleScreen (SDL_Window* &window, bool &quit, bool firstTime, double& systemVolume, double& musicVolume, int& songIdx);
        
};

#endif