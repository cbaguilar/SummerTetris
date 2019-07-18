UNAME_S := $(shell uname)

ifeq ($(OS),Windows_NT)
	CXXFLAGS += -lncursesw -static-libgcc -static-libstdc++ 
else
	
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		CXXFLAGS += -lncurses -pthread -I../ledDisplay/rpi-rgb-led-matrix/include -L../ledDisplay/rpi-rgb-led-matrix/lib/ -lrgbmatrix

	endif
endif


game.out: game.cpp
	g++  -o  $@ $< -g $(CXXFLAGS)
