# Tetris
This is my replica version of the famous Tetris game

I made this game on Linux, so I'm sorry if it cannot operate functionally on other platform

## Execute
To run the game, clone the repo to your device, type make to create the executable tetris.exe. Then type ./tetris.exe to run the game

```bash
make
./tetris.exe
```

To clean the .o file, type make clean

```bash
make clean
```

I also provided an tetris.exe executable, so you can just type ./tetris.exe to run it

```bash
./tetris.exe
```

## Game details
This is a replica of the famous game Tetris. The rules remain the same as the original version and can be summarized as follow:
- The aim of the game is trying to clear as many lines as possible in the 20x10 grid
- There are seven blocks released in batch, which means that all the seven blocks will fall down before new batch come along
- The blocks can be rotated
- About 0.5 seconds after the block interact with a surface, it will be locked and unmovable
- There will be a window to display the next block, another to display the lines as well as the score and high score of the player

## Additional feature
I have created a few additional features as follow:
- A setting screen where player can change the music and system volume with a drag bar. Player can also change the background song.
- After the game, the player has the option to return to the home screen or continue playing
- High score

## Note
- Most of the graphics are taken from the game [Tetris effect](https://www.tetriseffect.game/)
- Sound effects and music are taken from Youtube
P/S: Sorry that I used Internet picture so the visual is a bit patched up but I simply don't have the ability to draw them myself