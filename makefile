CC=g++
CFLAGS=

all:
	g++ -o cmap.x cmap.cpp fio.cpp

clean:
	rm -rf *.out *.dat *.o *.x
