# https://anguscheng.com/post/2023-12-12-wasm-game-in-c-raylib/

.PHONY: run clean

build: src/*.c
	gcc -o build $^ $(shell pkg-config --libs --cflags raylib)

run: build
	./build

clean:
	rm launcher/app