CC = g++
CFLAGS = -Wall -g
SRC = Board.cpp \
	Button.cpp \
	EndGameNoti.cpp \
	LTexture.cpp \
	MainGame.cpp \
	NextBlock.cpp \
	ProgressBar.cpp \
	ScoreBoard.cpp \
	SettingScreen.cpp \
	Shape.cpp \
	TitleScreen.cpp \
	Window.cpp
LIBS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

all: tetris.exe

tetris.exe: $(SRC:.cpp=.o)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

%.o: %.cpp %.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o