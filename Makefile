all: prog exec clean

prog:
	g++ main.cpp -fPIC interface/interface.cpp fourier/fourier.cpp -o prog -lsfml-graphics -lsfml-window -lsfml-system `pkg-config --cflags --libs opencv4`

exec:
	./prog

clean:
	rm prog