CXX = g++
CXXFLAGS = -Wall -std=c++14
INCLUDE = -I./
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

all: main

main: game.o main.o enemy_ship.o player_ship.o input.o score_panel.o collision_handler.o shot.o
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o main game.o main.o enemy_ship.o player_ship.o input.o score_panel.o collision_handler.o shot.o $(SFML_LIBS)

_DEPS = window.h Game.h Ship.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o window.o Game.o Ship.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -std=c++14 -c -o $@ $< $(CFLAGS)

player_ship.o: player_ship.cc player_ship.h
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c player_ship.cc

input.o: input.cc input.h
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c input.cc

score_panel.o: score_panel.cc score_panel.h
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c score_panel.cc

collision_handler.o: collision_handler.cc collision_handler.h
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c collision_handler.cc

shot.o: shot.cc shot.h
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c shot.cc

clean:
	rm -f *.o main
