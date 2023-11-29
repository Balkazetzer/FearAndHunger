#OBJS specifies which files to compile as part of the project
OBJS = $(wildcard src/*.cpp)
#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = bin/fearandhunger

#This is the target that compiles our executable
fearandhunger : $(OBJS) 
	g++ -std=c++17 -g $(OBJS) -I include -I/mingw64/include/SDL2 -L/mingw64/lib -w -Wl,-subsystem,windows -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -o $(OBJ_NAME)

all : fearandhunger

run: fearandhunger
	$(OBJ_NAME)