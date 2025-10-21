CC=g++
SRC=interface/interface.cpp fourier/fourier.cpp
CFLAGS=-lsfml-graphics -lsfml-window -lsfml-system `pkg-config --cflags --libs opencv4`

all: prog exec clean

prog:
	$(CC) main.cpp -fPIC $(SRC) -o prog $(CFLAGS)

exec:
	./prog

clean:
	rm prog