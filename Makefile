CXX = g++
CXXFLAGS = -Wall -std=c++14
INCLUDE = -I./ -I./game_objects
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -L/usr/lib/

all: main

main: game.o window.o main.o
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o main game.o window.o main.o $(LDFLAGS)

game.o: game.cc game.h
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c game.cc

window.o: window.cc window.h
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c window.cc

main.o: main.cc
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c main.cc

clean:
	rm -f *.o main
