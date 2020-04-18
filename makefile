CC=g++
CFLAGS=-fopenmp
FDEBUG=-Wall
FFAST=-fopenmp

DEPS=input.o output.o observables.o spectral_density.o spin_boson.o cmap.o

all: $(DEPS)
	$(CC) -o cmap.x $^ $(CFLAGS)

debug: CFLAGS=$(FDEBUG)
debug: $(DEPS)
	$(CC) -o cmap.x $^ $(FDEBUG)

fast: $(DEPS)
	$(CC) -o cmap.x $^ $(FFAST)

%.o: %.cpp
	$(CC) -c $^ $(CFLAGS)

clean:
	rm -rf *.out *.dat *.o *.x
