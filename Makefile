.PHONY: run clean

demo_executable: framework.o demo/*
	cp src/rpg_project_framework.h demo/rpg_project_framework.h
	gcc -o demo_executable framework.o demo/*.c -lSDL2_image $(shell sdl2-config --cflags) $(shell sdl2-config --libs)
	rm demo/rpg_project_framework.h

framework.o: src/*
	gcc -c -o framework.o src/*.c

run: demo_executable
	./demo_executable

clean:
	rm demo_executable
	rm framework.o