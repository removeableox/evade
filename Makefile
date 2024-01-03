CC = x86_64-w64-mingw32-g++
INCLUDES = -I./include -I/usr/include
LIBS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
SRCDIR = ./src
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
	EXECUTABLE = main.exe

%.o: %.cpp
	$(CC) -c $< -o $@ $(INCLUDES)

$(EXECUTABLE): $(OBJECTS)
	$(CC) -o $@ $^ $(LIBS)

.PHONY: clean

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

