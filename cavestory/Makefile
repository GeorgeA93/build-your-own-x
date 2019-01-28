CC=g++
SOURCES=src/*.cpp
OBJ_NAME=cavestory
COMPILER_FLAGS=-w
LINKER_FLAGS=-lSDL2 -lSDL2_image

all : $(SOURCES)
				$(CC) $(SOURCES) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

clean :
	rm $(OBJ_NAME)
