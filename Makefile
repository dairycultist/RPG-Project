.PHONY: run clean

demo: src/*
	gcc -o demo src/main.c -lSDL2_image $(shell sdl2-config --cflags) $(shell sdl2-config --libs)

run: demo
	./demo

clean:
	rm demo