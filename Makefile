CXX = g++
CXXFLAGS = -g -Wall -std=c++17
INCLUDE = -I./
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system
OBJS = game.o main.o player_ship.o input.o shot.o window.o shot_group.o enemy_ship.o collision_handler.o thread/cpu.o thread/debug.o thread/main_class.o thread/semaphore.o thread/system.o thread/thread.o

all: $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o main $(OBJS) $(SFML_LIBS)

game.o: game.cc game.h
	$(CXX) -g $(CXXFLAGS) $(INCLUDE) -c game.cc

main.o: main.cc
	$(CXX) -g $(CXXFLAGS) $(INCLUDE) -c main.cc

player_ship.o: player_ship.cc player_ship.h
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c player_ship.cc

input.o: input.cc input.h
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c input.cc

shot.o: shot.cc shot.h
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c shot.cc

window.o: window.cc window.h
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c window.cc

shot_group.o: shot_group.cc shot_group.h
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c shot_group.cc

enemy_ship.o: enemy_ship.cc enemy_ship.h
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c enemy_ship.cc

collision_handler.o: collision_handler.cc collision_handler.h
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c collision_handler.cc

thread/%.o: thread/%.cc thread/%.h
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -f *.o thread/*.o main
