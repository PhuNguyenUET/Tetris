#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "LTexture.cpp"
#include "Button.cpp"

class ProgressBar {
    private:
        int xPos;
        int yPos;
        int pointerPos;
        LTexture* bar;
        double volume;
        LTexture* circle;
        int circlePosX = barWidth + barPos.x;
    public:
        SDL_Point barPos;
        const int barWidth = 350;
        const int barHeight = 20;
        ProgressBar (SDL_Renderer* &renderer, int x, int y, double& volume) {
            bar = new LTexture(barWidth, barHeight);
            circle = new LTexture(30, 30);
            bar->loadFromFile("Graphics/TheBar.png", renderer);
            circle->loadFromFile("Graphics/BlackCircle.png", renderer);
            barPos.x = x;
            barPos.y = y;
            circlePosX = volume * barWidth + barPos.x - 20;
        }

        void render (SDL_Renderer* &renderer) {
            bar->render(barPos.x, barPos.y, renderer);
            circle->render(circlePosX, barPos.y - 5, renderer);
        }

        void handleEvent (SDL_Event e, double& volume) {
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                int x, y;
                SDL_GetMouseState(&x, &y);

                bool inside = true;

                if (x < barPos.x) {
                    inside = false;
                } 
                if (x > barPos.x + barWidth) {
                    inside = false;
                }
                if (y < barPos.y) {
                    inside = false;
                }
                if (y > barPos.y + barHeight) {
                    inside = false;
                }

                if (inside) {
                    circlePosX = x - 15;
                    if (x < 15) {
                        circlePosX = x;
                    }
                    volume = (x - barPos.x) / (double)barWidth;
                }
            }
        }


};