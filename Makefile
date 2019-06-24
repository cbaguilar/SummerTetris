UNAME_S := $(shell uname)

ifeq ($(OS),Windows_NT)
	CXXFLAGS += -lncursesw
else
	
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		CXXFLAGS += -lncurses
	endif
endif


game: game.cpp
	g++  -o  $@ $< -g $(CXXFLAGS)
