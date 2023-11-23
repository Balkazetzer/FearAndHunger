#OBJS specifies which files to compile as part of the project
OBJS = src/01_hello_SDL.cpp

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = bin/01_hello_SDL

#This is the target that compiles our executable
tutorial1 : src/*
	g++ src/01_hello_SDL.cpp -IC:\msys64\mingw64\include\SDL2 -LC:\MinGW\lib -w -Wl,-subsystem,windows -lmingw32 -lSDL2main -lSDL2 -o bin/tutorial0

tutorial0 : src/*
	g++ src/02_getting_an_image_on_the_screen.cpp -IC:\msys64\mingw64\include\SDL2 -LC:\MinGW\lib -w -Wl,-subsystem,windows -lmingw32 -lSDL2main -lSDL2 -o bin/tutorial1

all : tutorial0 tutorial1


runT0: 
	./bin/tutorial0

runT1: 
	./bin/tutorial1

Objetivo : Dependencias
	Comandos