CC=g++
CFLAGS=-fopenmp
FDEBUG=-Wall -fopenmp
FFAST=-O3 -fopenmp

DEPS=input.o spectral_density.o spin_boson.o cmap.o

all: $(DEPS)
	$(CC) -o cmap.x $^ $(CFLAGS)

debug: $(DEPS)
	$(CC) -o cmap.x $^ $(FDEBUG)

fast: $(DEPS)
	$(CC) -o cmap.x $^ $(FFAST)

%.o: %.cpp
	$(CC) -c $^ $(CFLAGS)

clean:
	rm -rf *.out *.dat *.o *.x
