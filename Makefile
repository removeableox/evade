CC = g++

INCLUDE = -I ./include

LIBS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

 main:
	${CC} -o main ./src/*.cpp ${INCLUDE} ${LIBS}
