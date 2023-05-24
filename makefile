CC=g++
CFLAGS=-fopenmp -I /usr/local/include/eigen3
FDEBUG=-Wall -I /usr/local/include/eigen3
FFAST=-O3 -fopenmp -I /usr/local/include/eigen3

DEPS=input.o output.o observables.o spectral_density.o spin_boson.o dynamics.o cmap.o

all: $(DEPS)
	$(CC) -o cmap.x $^ $(CFLAGS)

debug: CFLAGS=$(FDEBUG)
debug: $(DEPS)
	$(CC) -o cmap.x $^ $(FDEBUG)

fast: CFLAGS=$(FFAST)
fast: $(DEPS)
	$(CC) -o cmap.x $^ $(FFAST)

%.o: %.cpp
	$(CC) -c $^ $(CFLAGS)

clean:
	rm -rf *.out *.dat *.o *.x
