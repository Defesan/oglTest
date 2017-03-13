OBJS = oglTest.cpp

OBJ_NAME = oglTest

CC = g++

COMPILER_FLAGS = -Wall -std=c++11

LINKER_FLAGS = -lSDL2 -lSDL2_test -lGL -lGLU

all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
