FILES=main.cpp
OUTPUT=out
INCLUDES=-I/usr/local/include/SFML
LIBS=-lsfml-graphics -lsfml-window -lsfml-system
STD=-std=c++14

debug:
	g++ $(FILES) -o $(OUTPUT) $(INCLUDES) $(LIBS) $(STD) -DDEBUG

all:
	g++ $(FILES) -o $(OUTPUT) $(INCLUDES) $(LIBS) $(STD)