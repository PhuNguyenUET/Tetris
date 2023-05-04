CC = g++
CFLAGS = -Wall -g
SRC = src/Board.cpp \
	src/Button.cpp \
	src/EndGameNoti.cpp \
	src/LTexture.cpp \
	src/MainGame.cpp \
	src/NextBlock.cpp \
	src/ProgressBar.cpp \
	src/ScoreBoard.cpp \
	src/SettingScreen.cpp \
	src/Shape.cpp \
	src/TitleScreen.cpp \
	src/Window.cpp
LIBS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

all: tetris.exe

tetris.exe: $(SRC:src/%.cpp=%.o)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

%.o: src/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o