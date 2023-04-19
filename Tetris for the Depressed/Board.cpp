#include <iostream>
#include "Board.h"

        Board::Board (SDL_Renderer* &renderer) {
            loadMedia(renderer);
            clearLineSound = Mix_LoadWAV("Audio/ClearLines.wav");
            clearMultipleSound = Mix_LoadWAV("Audio/ClearMultipleLines.wav");
        }

        Board::~Board () {
            Mix_FreeChunk(clearLineSound);
            clearLineSound = NULL;
        }

        void Board::loadMedia (SDL_Renderer* &renderer) {
            tiles = new LTexture(22 * 8, 22);
            tiles->loadFromFile("Graphics/tiles.png", renderer);

            for (int i = 0; i < 8; i++) {
                indTile[i].x = 18 * i;
                indTile[i].y = 0;
                indTile[i].w = 18;
                indTile[i].h = 18;
            }
        }

        void Board::handleEvent (SDL_Event e, Shape* shape, vector <vector <int>>& board, bool& merge, double& systemVolume) {
            if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_LEFT:
                        shape -> moveLeft(board);
                        break;
                    case SDLK_RIGHT:
                        shape -> moveRight(board);
                        break;
                    case SDLK_UP:
                        shape->rotateUp(board);
                        break;
                    case SDLK_DOWN:
                        shape -> rotateDown(board);
                        break;
                    case SDLK_SPACE:
                        shape->hardDrop(board, merge, systemVolume);
                        break;
                }
            }
        }

        void Board::render (vector <vector <int>>& board, SDL_Renderer* renderer) {
            for (int i = 0; i < PLAY_ROW; i++) {
                for (int j = 0; j < PLAY_COL; j++) {
                    if (board[i][j] != 0) {
                        if (board[i][j] < 10) {
                            tiles->render(j * 22 + 490, i * 22 + 47, renderer, &indTile[board[i][j]]);
                        } else {
                            tiles->render(j * 22 + 490, i * 22 + 47, renderer, &indTile[board[i][j] - 10]);
                        }
                    }
                    if (board[i][j] == -1) {
                        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                        SDL_RenderDrawLine(renderer, 490 + 22 * j, 47 + 22 * i, 490 + 22 * (j + 1), 47 + 22 * i);
                        SDL_RenderDrawLine(renderer, 490 + 22 * (j + 1), 47 + 22 * i, 490 + 22 * (j + 1), 47 + 22 * (i + 1));
                        SDL_RenderDrawLine(renderer, 490 + 22 * (j + 1), 47 + 22 * (i + 1), 490 + 22 * (j), 47 + 22 * (i + 1));
                        SDL_RenderDrawLine(renderer, 490 + 22 * j, 47 + 22 * i, 490 + 22 * (j), 47 + 22 * (i + 1));
                    }
                }
            }
        }

        void Board::clearHover (vector <vector <int>>& board) {
            for (int i = 0; i < 20; i++) {
                for (int j = 0; j < 10; j++) {
                    if (board[i][j] == -1) {
                        board[i][j] = 0;
                    }
                }
            }
        }

        bool Board::isGameOver (vector <vector <int>> & board) {
            for (int i = 0; i < PLAY_COL; i++) {
                if (board[0][i] >= 10) {
                    return true;
                }
            }
            return false;
        }

        void Board::clearLines(vector <vector<int>>& board, vector <bool>& rowState, int& lines, int& score, int& highScore, double& systemVolume) {
            int numClear = 0;
            for (int i = 0; i < PLAY_ROW; i++) {
                bool clear = true;
                rowState[i] = true;
                for (int j = 0; j < PLAY_COL; j++) {
                    if (board[i][j] < 10) {
                        clear = false;
                        rowState[i] = false;

                    }
                } 
                if (clear) {
                    for (int j = 0; j < PLAY_COL; j++) {
                        board[i][j] = 0;
                    }
                    lines ++;
                    numClear ++;
                }
            }
            for (int i = PLAY_ROW - 2; i >= 0; i--) {
                if (!rowState[i]) {
                    int idx = i;
                    int curRow = idx;
                    while (idx < PLAY_ROW && rowState[++idx]) {
                        // get to the lowest clear lines
                    }        
                    idx --;
                    for (int j = 0; j < PLAY_COL; j++) {
                        if (board[curRow][j] >= 10) {
                            board[idx][j] = board[curRow][j];
                        }
                    }
                    if (idx != curRow) {
                        for (int j = 0; j < PLAY_COL; j++) {
                            board[curRow][j] = 0;
                        }
                        rowState[curRow] = true;
                        rowState[idx] = false;
                    }
                }
            }
            Mix_VolumeChunk(clearLineSound, MIX_MAX_VOLUME * systemVolume);
            Mix_VolumeChunk(clearMultipleSound, MIX_MAX_VOLUME * systemVolume);
            if (numClear == 1) {
                score += 10;
                Mix_PlayChannel(-1, clearLineSound, 0);
            } else if (numClear == 2) {
                score += 12;
                Mix_PlayChannel(-1, clearMultipleSound, 0);
            } else if (numClear > 2) {
                score += (10* numClear) + ((numClear - 1) * (2 + numClear) * 3 / 4);
                Mix_PlayChannel(-1, clearMultipleSound, 0);
            }
            if (score >= highScore) {
                highScore = score;
            }
        }