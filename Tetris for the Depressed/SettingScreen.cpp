#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "ProgressBar.cpp"

using std::vector;

class SettingScreen {
    private:
        vector <string> songsList = {"Classic Theme Song", "Hold on Tight", "Dissipate", "Natsukashii"};
        const int UIwidth = 960;
        const int UIheight = 600;

        Button* exitButton;
        Button* changeButton;
        LTexture* SettingsWindow;

        SDL_Texture* sysTexture = NULL;
        SDL_Texture* music = NULL;
        SDL_Texture* songs = NULL;
        SDL_Texture* songName = NULL;

        ProgressBar* musicBar;
        ProgressBar* systemBar;

        TTF_Font* font = NULL;

        int x, y;
    public:
        SettingScreen(SDL_Renderer* &renderer, int x, int y, double& systemVolume, double& musicVolume, int& currentMusic) {
            TTF_Init();
            font = TTF_OpenFont("Font/Font.ttf", 30);

            SettingsWindow = new LTexture(UIwidth, UIheight);
            SettingsWindow->loadFromFile("Graphics/SettingsUI.png", renderer);
            exitButton = new Button(renderer, "Graphics/ExitButton.png", 150, 75);
            changeButton = new Button(renderer, "Graphics/ChangeButton.png", 40, 40);
            this->x = x;
            this->y = y;
            exitButton->setPos(x + (UIwidth - 250) / 2 + 50, y + UIheight - 220);
            changeButton->setPos(x + UIwidth - 200, y + UIheight - 300);
            musicBar = new ProgressBar(renderer, x + 400, y + 170, musicVolume);
            systemBar = new ProgressBar(renderer, x + 400, y + 240, systemVolume);

            loadFromRenderedText(music, "Music Volume", renderer);
            loadFromRenderedText(sysTexture, "System Volume", renderer);
            loadFromRenderedText(songs,"Song Option", renderer);
            loadFromRenderedText(songName, songsList[currentMusic], renderer);
        }

        void free (SDL_Texture* &texture) {
            if (texture != NULL) {
                SDL_DestroyTexture(texture);
                texture = NULL;
            }
        }

        ~SettingScreen () {
            free(music);
            free(sysTexture);
            free(songs);
            TTF_CloseFont(font);
            font = NULL; 
        }

        void loadFromRenderedText (SDL_Texture* &texture, string text, SDL_Renderer* &renderer) {
            free (texture);

            SDL_Color color = {255, 255, 255, 255};
            SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);

            texture = SDL_CreateTextureFromSurface(renderer, textSurface);

            SDL_FreeSurface(textSurface);
        }

        void handleEvent (SDL_Renderer* &renderer, SDL_Event e, bool& openSetting, double& systemVolume, double& musicVolume, int& currentMusic) {
            bool close = false;
            exitButton->handleEvent(e, close);
            if (close) {
                openSetting = false;
            } else {
                bool changeMusic = false;
                musicBar->handleEvent(e, musicVolume);
                systemBar->handleEvent(e, systemVolume);
                changeButton->handleEvent(e, changeMusic);
                if (changeMusic) {
                    currentMusic = (currentMusic + 1) % 4;
                    changeMusic = false;
                    loadFromRenderedText(songName, songsList[currentMusic], renderer);
                }
            }
        }

        void render (SDL_Renderer* &renderer, int& currentMusic) {
            SDL_Rect musicRect = {x + 150, y + 150, 200, 50};
            SDL_Rect systemRect = {x + 150, y + 220, 200, 50};
            SDL_Rect songRect = {x + 150, y + 290, 200, 50};
            SDL_Rect songNameRect;
            switch (currentMusic) {
                case 0:
                    songNameRect = {x + 400, y + 290, 300, 50};
                    break;
                case 1:
                    songNameRect = {x + 400, y + 290, 220, 50};
                    break;
                case 2:
                    songNameRect = {x + 400, y + 290, 150, 50};
                    break;
                case 3: 
                    songNameRect = {x + 400, y + 290, 180, 50};
                    break;
            }
            SettingsWindow->render(x, y, renderer);
            SDL_RenderCopy(renderer, music, NULL, &musicRect); 
            SDL_RenderCopy(renderer, sysTexture, NULL, &systemRect);
            SDL_RenderCopy(renderer, songs, NULL, &songRect);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_Rect rect = {x + 400, y + 290, 330, 50};
            SDL_RenderFillRect(renderer, &rect);
            SDL_RenderCopy(renderer, songName, NULL, &songNameRect);
            exitButton->render(renderer);
            changeButton->render(renderer);
            musicBar->render(renderer);
            systemBar->render(renderer);
        }
};