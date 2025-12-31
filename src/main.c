#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "sprite.h"

// to start, lets just get a character rendering and controllable (reading ALL data externally)

// screen size of GBA; PMD uses 32x32 though many characters mostly fit into 24x24
#define DISPLAY_WIDTH 240
#define DISPLAY_HEIGHT 160

#define FALSE 0
#define TRUE 1

static SDL_Window *window;
static SDL_Renderer *renderer;
static SDL_Texture *display_buffer;

int main() {

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("Error initializing SDL:\n%s\n", SDL_GetError());
		return 1;
	}

	window = SDL_CreateWindow("RPG", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, DISPLAY_WIDTH * 2, DISPLAY_HEIGHT * 2, SDL_WINDOW_RESIZABLE);

	if (!window) {
		printf("Error creating window:\n%s\n", SDL_GetError());
		return 1;
    }

	renderer = SDL_CreateRenderer(window, -1, 0);

	if (!renderer) {
		printf("Error creating renderer:\n%s\n", SDL_GetError());
		return 1;
	}

	display_buffer = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, DISPLAY_WIDTH, DISPLAY_HEIGHT);

	if (!display_buffer) {
		printf("Error creating display buffer:\n%s\n", SDL_GetError());
		return 1;
	}

	// initialize
	initialize_sprite_handler(renderer);

	Sprite *snivy = load_sprite("src/Idle-Anim.png");

	// process events until window is closed
	SDL_Event event;
	SDL_Rect letterbox = {0, 0, DISPLAY_WIDTH * 2, DISPLAY_HEIGHT * 2};

	int running = TRUE;

	while (running) {

		while (SDL_PollEvent(&event)) {

			if (event.type == SDL_QUIT) {

				running = FALSE;

			} else if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED) {

				#define MIN(a, b) ((a) > (b) ? (b) : (a))

				// dynamically change letterbox based on window resize
				letterbox.w = MIN(event.window.data1, event.window.data2 * (DISPLAY_WIDTH / (float) DISPLAY_HEIGHT));
				letterbox.h = MIN(event.window.data2, event.window.data1 / (DISPLAY_WIDTH / (float) DISPLAY_HEIGHT));

				letterbox.x = (event.window.data1 - letterbox.w) / 2;
				letterbox.y = (event.window.data2 - letterbox.h) / 2;

			} else if ((event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) && !event.key.repeat) {

				// event.key.keysym.scancode
				// SDL_SCANCODE_UP
			}
		}

		SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255); 			// clear window to grey
		SDL_RenderClear(renderer);
		SDL_SetRenderTarget(renderer, display_buffer); 				// set render target to display_buffer
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 			// clear display_buffer to black
		SDL_RenderClear(renderer);
		
		// TODO logic/rendering to display_buffer
		draw_subsprite(snivy, 0, 0, 0, 0, 32, 32, FALSE);

		SDL_SetRenderTarget(renderer, NULL); 						// reset render target back to window
		SDL_RenderCopy(renderer, display_buffer, NULL, &letterbox); // render display_buffer
		SDL_RenderPresent(renderer); 								// present rendered content to screen

		SDL_Delay(1000 / 60);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}