/*
 * hardware.c is a IO abstraction layer (provides a window, rendering tools, and input reports)
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "hardware.h"

#define FALSE 0
#define TRUE 1

/*
 * rendering
 */
// Sprite *load_sprite(const char *path) {

// 	Sprite *sprite = malloc(sizeof(Sprite));

// 	sprite->sdl_texture = IMG_LoadTexture(renderer, path);

// 	if (!sprite->sdl_texture) {

// 		printf("Could not load %s (non-fatal error)\n", path);
// 		sprite->w = 0;
// 		sprite->h = 0;
// 		return sprite;
// 	}

// 	SDL_QueryTexture(sprite->sdl_texture, NULL, NULL, &sprite->w, &sprite->h);

// 	return sprite;
// }

// void draw_sprite(Sprite *sprite, int x, int y, int BOOL_flip) {

// 	SDL_Rect dst_rect = { x, y, sprite->w, sprite->h };

// 	SDL_RenderCopyEx(renderer, sprite->sdl_texture, NULL, &dst_rect, 0.0, NULL, BOOL_flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
// }

// void draw_subsprite(Sprite *sprite, int x, int y, int sample_x, int sample_y, int sample_w, int sample_h, int BOOL_flip) {

// 	SDL_Rect src_rect = { sample_x, sample_y, sample_w, sample_h };
// 	SDL_Rect dst_rect = { x, y, sample_w, sample_h };

// 	SDL_RenderCopyEx(renderer, sprite->sdl_texture, &src_rect, &dst_rect, 0.0, NULL, BOOL_flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
// }

// void free_sprite(Sprite *sprite) {
	
// 	SDL_DestroyTexture(sprite->sdl_texture);
// 	free(sprite);
// }

typedef struct {

	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *display_buffer;
	int width;
	int height;
	int wait_time_ms;
	SDL_Rect letterbox;

} Window;

AbstractWindow *create_window(const char *title, int w, int h, int fps) {

	Window *window = malloc(sizeof(Window));

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("Error initializing SDL:\n%s\n", SDL_GetError());
		return NULL;
	}

	window->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_RESIZABLE);

	if (!window->window) {
		printf("Error creating window:\n%s\n", SDL_GetError());
		return NULL;
    }

	window->renderer = SDL_CreateRenderer(window->window, -1, 0);

	if (!window->renderer) {
		printf("Error creating renderer:\n%s\n", SDL_GetError());
		return NULL;
	}

	window->display_buffer = SDL_CreateTexture(window->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);

	if (!window->display_buffer) {
		printf("Error creating display buffer:\n%s\n", SDL_GetError());
		return NULL;
	}

	window->width = w;
	window->height = h;
	window->wait_time_ms = 1000 / fps;
	window->letterbox.x = 0;
	window->letterbox.y = 0;
	window->letterbox.w = w;
	window->letterbox.h = h;

	return window;
}

void present(AbstractWindow *abstract_window) {

	Window *window = (Window *) abstract_window;

	/*
	 * TODO update input reports
	 */
	SDL_Event event;

	while (SDL_PollEvent(&event)) {

		if (event.type == SDL_QUIT) {

			exit(0); // temp until we get a "quit" input report

		} else if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED) {

			#define MIN(a, b) ((a) > (b) ? (b) : (a))

			// dynamically change letterbox based on window resize
			window->letterbox.w = MIN(event.window.data1, event.window.data2 * (window->width / (float) window->height));
			window->letterbox.h = MIN(event.window.data2, event.window.data1 / (window->width / (float) window->height));

			window->letterbox.x = (event.window.data1 - window->letterbox.w) / 2;
			window->letterbox.y = (event.window.data2 - window->letterbox.h) / 2;

		} else if ((event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) && !event.key.repeat) {

			// event.key.keysym.scancode
			// SDL_SCANCODE_UP
		}
	}

	/*
	 * actual presentation
	 */
	SDL_SetRenderTarget(window->renderer, NULL); 					// reset render target back to window
	SDL_RenderCopy(window->renderer, window->display_buffer,		// render display_buffer to window
		NULL, &window->letterbox);
	SDL_RenderPresent(window->renderer); 							// present rendered content to screen

	SDL_SetRenderDrawColor(window->renderer, 40, 40, 40, 255); 		// clear window to grey
	SDL_RenderClear(window->renderer);
	SDL_SetRenderTarget(window->renderer, window->display_buffer); 	// set render target to display_buffer
	SDL_SetRenderDrawColor(window->renderer, 0, 0, 0, 255); 		// clear display_buffer to black
	SDL_RenderClear(window->renderer);

	SDL_Delay(window->wait_time_ms);
}

void destroy_window(AbstractWindow *abstract_window) {

	Window *window = (Window *) abstract_window;

	SDL_DestroyRenderer(window->renderer);
	SDL_DestroyWindow(window->window);
	// also destroy window->display_buffer
	SDL_Quit();
}