#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "rpg_project_framework.h"

#define FALSE 0
#define TRUE 1

static SDL_Window *window;
static SDL_Renderer *renderer;
static SDL_Texture *display_buffer;

// helpers
#include "sprite.c"
// #include "character.c"
// #include "event.c"

// singletons (contain persistent data, ones that represent scenes also have process functions)
#include "worldmap.c"
// #include "battle.c"
// #include "shop.c"
// (party info, items, arbitrary data void *, etc)

// #include "save.c" // contains save() (exposed to programmer, saves all persistent data to a file) and load() (run automatically on start, loads persistent data from file)

static Scene current_scene;

void set_scene(Scene scene) {

	current_scene = scene;
}

int main() {

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("Error initializing SDL:\n%s\n", SDL_GetError());
		return 1;
	}

	window = SDL_CreateWindow(get_rpg_name(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, DISPLAY_WIDTH * 2, DISPLAY_HEIGHT * 2, SDL_WINDOW_RESIZABLE);

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

	// initialize
	init();

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
		
		// logic/rendering to display_buffer
		switch (current_scene) {
			
			case Worldmap:
				worldmap_process();
				break;

			default:
				break;
		}

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