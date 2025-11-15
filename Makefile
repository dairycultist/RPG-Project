.PHONY: run clean

demo/demo_executable: demo/framework.o demo/*.c demo/*.png
	cp src/rpg_project_framework.h demo/rpg_project_framework.h
	cd demo ; gcc -o demo_executable framework.o *.c -lSDL2_image $(shell sdl2-config --cflags) $(shell sdl2-config --libs)
	rm demo/rpg_project_framework.h

demo/framework.o: src/*
	gcc -c -o demo/framework.o src/main.c

run: demo/demo_executable
	./demo/demo_executable

clean:
	rm demo/demo_executable
	rm demo/framework.o