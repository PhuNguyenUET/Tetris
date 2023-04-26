#ifndef SETTINGSCREEN_H
#define SETTINGSCREEN_H

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "LTexture.h"
#include "ProgressBar.h"
#include "Button.h"

using std::string;
using std::vector;

class SettingScreen
{
private:
    vector<string> songsList = {"Classic Theme Song", "Hold on Tight", "Dissipate", "Natsukashii", "WillPower"};
    const int UIwidth = 960;
    const int UIheight = 600;

    Button *exitButton;
    Button *changeButton;
    LTexture *SettingsWindow;

    SDL_Texture *sysTexture = NULL;
    SDL_Texture *music = NULL;
    SDL_Texture *songs = NULL;
    SDL_Texture *songName = NULL;

    ProgressBar *musicBar;
    ProgressBar *systemBar;

    TTF_Font *font = NULL;

    int x, y;

public:
    SettingScreen(SDL_Renderer *&renderer, int x, int y, double &systemVolume, double &musicVolume, int &currentMusic);
    void free(SDL_Texture *&texture);
    ~SettingScreen();
    void loadFromRenderedText(SDL_Texture *&texture, string text, SDL_Renderer *&renderer);
    void handleEvent(SDL_Renderer *&renderer, SDL_Event e, bool &openSetting, double &systemVolume, double &musicVolume, int &currentMusic);
    void render(SDL_Renderer *&renderer, int &currentMusic);
};

#endif