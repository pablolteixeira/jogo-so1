CXX = g++
CXXFLAGS = -Wall -std=c++14
INCLUDE = -I./
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

all: main

main: game.o main.o enemy_ship.o player_ship.o input.o
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o main game.o main.o enemy_ship.o player_ship.o input.o $(SFML_LIBS)

game.o: game.cc game.h
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c game.cc

main.o: main.cc
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c main.cc

enemy_ship.o: enemy_ship.cc enemy_ship.h
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c enemy_ship.cc

player_ship.o: player_ship.cc player_ship.h
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c player_ship.cc

input.o: input.cc input.h
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c input.cc

clean:
	rm -f *.o main
