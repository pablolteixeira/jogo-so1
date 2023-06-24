CC = g++
CFLAGS = -Wall -std=c++14
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

OBJS = main.o game.o game_objects/collision_handler.o game_objects/enemy_spaceship.o game_objects/shot.o \
       game_objects/spaceship.o screen/score_panel.o screen/window.o thread/cpu.o thread/debug.o thread/main_class.o \
       thread/semaphore.o thread/system.o thread/thread.o

all: game

game: $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.cc
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJS) game
