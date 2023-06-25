IDIR =.
CC=g++
LDLIBS =  -lsfml-graphics -lsfml-window -lsfml-system -lm  -lpng -g
CFLAGS=-I$(IDIR) -g -Wextra -Wall

LDFLAGS= $(CFLAGS)

ODIR=.
LIBS= $(LDLIBS) $(LDFLAGS)

_DEPS = window.h Game.h Ship.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o window.o Game.o Ship.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -std=c++14 -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -std=c++14 -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ main
