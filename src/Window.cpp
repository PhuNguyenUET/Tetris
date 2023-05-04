#include <iostream>

#include "../Header/Window.h"

void Window::init(SDL_Window *&window)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    int imgFlag = IMG_INIT_PNG;
    IMG_Init(imgFlag);

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
}

void Window::loadMedia(int songIdx)
{
    bg = new LTexture(SCREEN_WIDTH, SCREEN_HEIGHT);
    bg->loadFromFile("Graphics/Tetris_BackGround.png", renderer);
    tutorial = new LTexture(244, 400);
    tutorial->loadFromFile("Graphics/Tutorial.png", renderer);
    endGame = new LTexture(SCREEN_WIDTH, SCREEN_HEIGHT);
    endGame->loadFromFile("Graphics/EndGame.png", renderer);
    nxtBlock->loadMedia(renderer);

    endGameSound = Mix_LoadWAV("Audio/GameOver.wav");
    // Change the themesong
    switch (songIdx)
    {
    case 0:
        themeSong = Mix_LoadMUS("Audio/TetrisSoundTrackOriginal.wav");
        break;
    case 1:
        themeSong = Mix_LoadMUS("Audio/TetrisSoundTrackWithLyrics.wav");
        break;
    case 2:
        themeSong = Mix_LoadMUS("Audio/Dissipate.wav");
        break;
    case 3:
        themeSong = Mix_LoadMUS("Audio/Natsukashii.wav");
        break;
    case 4:
        themeSong = Mix_LoadMUS("Audio/WillPower.wav");
        break;
    }
}

void Window::close()
{
    SDL_DestroyRenderer(renderer);
    renderer = NULL;

    Mix_FreeChunk(endGameSound);
    endGameSound = NULL;

    Mix_FreeMusic(themeSong);
    themeSong = NULL;

    Mix_Quit();
    IMG_Quit();
}

void Window::kill(SDL_Window *&window)
{
    SDL_DestroyWindow(window);
    window = NULL;

    SDL_Quit();
}

// Sorry I crammed them all into constructor 
Window::Window(SDL_Window *&window, bool &quit, bool &playNext, double &systemVolume, double &musicVolume, int &songIdx, bool &turnBack)
{
    // read/write from file
    std::fstream file("src/HighScore.txt");
    file >> highScore;
    file.seekg(0);
    // Create the board
    for (int i = 0; i < PLAY_ROW; i++)
    {
        vector<int> tmp;
        for (int j = 0; j < PLAY_COL; j++)
        {
            tmp.push_back(0);
        }
        board.push_back(tmp);
        rowState.push_back(true);
    }

    init(window);
    loadMedia(songIdx);

    bool startCount = true;
    SDL_Event e;
    int prevTime = 0;
    int lines = 0;
    int score = 0;
    int prevScore = score;
    int prevLockTime = 0;

    // First-time initiation before entering the game loop
    shape = new Shape(shapeRotation);
    shape->generateNextBlock(nextShapeArr, shapeRotation, nxtColorIdx);
    brd = new Board(renderer);
    scoreBoard = new ScoreBoard(170, 50, 110, 50, renderer);
    LTexture *playArea = new LTexture(22 * 10, 22 * 20);
    playArea->loadFromFile("Graphics/PlayArea.png", renderer);

    scoreBoard->loadFromRenderedText("Your score: " + to_string(score), "Lines: " + to_string(lines), "High score: " + to_string(highScore), renderer);
    scoreBoard->render(SCREEN_WIDTH - 350, 300, renderer);

    nxtBlock->render(SCREEN_WIDTH - 350, 50, renderer, nextShapeArr, nxtColorIdx);
    tutorial->render(120, 70, renderer);

    // Change the volume based on setting
    Mix_VolumeMusic(MIX_MAX_VOLUME * musicVolume);
    Mix_VolumeChunk(endGameSound, MIX_MAX_VOLUME * systemVolume);
    Mix_PlayMusic(themeSong, -1);

    while (!quit && !end)
    {
        // Handle events
        // The time to calculate the fall time as well as the merge time
        int time = SDL_GetTicks();
        bool merge = false;
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            else
            {
                brd->handleEvent(e, shape, board, merge, systemVolume);
            }
        }

        if (score != prevScore)
        {
            scoreBoard->loadFromRenderedText("Your score: " + to_string(score), "Lines: " + to_string(lines), "High score: " + to_string(highScore), renderer);
            prevScore = score;
        }

        // After this time, the shape fall
        if (time - prevTime >= 700)
        {
            if (!shape->checkMerge(board))
            {
                shape->fall(startCount);
            }
            prevTime = time;
        }

        if (startCount)
        {
            // prevLockTime is the time the block started to interact with a surface
            prevLockTime = time;
        }

        // Merging, create new shape
        // hard-drop
        if (merge)
        {
            shape->updateBoard(board);
            shape->merge(board);
            shape = new Shape(board, end, nextShapeArr, nxtColorIdx);
            shape->generateNextBlock(nextShapeArr, shapeRotation, nxtColorIdx);
        }
        // Interact with surface
        else if (shape->checkMerge(board))
        {
            startCount = false;
            // After 500 ms, start merging
            if (time - prevLockTime >= 500)
            {
                shape->updateBoard(board);
                shape->merge(board);
                shape = new Shape(board, end, nextShapeArr, nxtColorIdx);
                shape->generateNextBlock(nextShapeArr, shapeRotation, nxtColorIdx);
                startCount = true;
            }
        }

        if (brd->isGameOver(board))
        {
            end = true;
        }

        // Render stuffs
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        bg->render(0, 0, renderer);
        playArea->render(490, 47, renderer);

        shape->hover(board, merge);
        shape->updateBoard(board);

        scoreBoard->render(SCREEN_WIDTH - 350, 300, renderer);
        nxtBlock->render(SCREEN_WIDTH - 350, 50, renderer, nextShapeArr, nxtColorIdx);

        tutorial->render(120, 70, renderer);

        brd->clearLines(board, rowState, lines, score, highScore, systemVolume);
        brd->render(board, renderer);

        brd->clearHover(board);

        SDL_RenderPresent(renderer);
    }
    if (score >= highScore)
    {
        file << score;
    }
    Mix_PlayChannel(-1, endGameSound, 0);
    Mix_HaltMusic();
    file.close();
    if (quit)
    {
        close();
        kill(window);
    }
    else
    {   
        // End-game window
        endGameNoti = new EndGameNoti(renderer);

        endGameNoti->loadScore(score, highScore, renderer);

        while (!quit && !playNext && !turnBack)
        {
            while (SDL_PollEvent(&e))
            {
                if (e.type == SDL_QUIT)
                {
                    quit = true;
                }
                else
                {
                    endGameNoti->handleEvent(e, playNext, turnBack);
                }
            }

            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderClear(renderer);
            endGame->render(0, 0, renderer);

            endGameNoti->render((SCREEN_WIDTH - 300) / 2, 150, renderer);

            SDL_RenderPresent(renderer);
        }

        scoreBoard->close();
        endGameNoti->close();
        if (quit)
        {
            close();
            kill(window);
        }
        else
        {
            close();
        }
    }
}