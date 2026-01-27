.PHONY: run clean

demo.out: src/*
	gcc -o demo.out src/*.c -lSDL2_image $(shell sdl2-config --cflags) $(shell sdl2-config --libs)

run: demo.out
	./demo.out

clean:
	rm demo.out