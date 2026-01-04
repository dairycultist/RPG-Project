/*
 * window.c is a IO abstraction layer (provides a window, rendering tools, and input reports)
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "window.h"
#include "logic.h"

#define FALSE 0
#define TRUE 1

#define FONT_FILENAME "src/vcr_osd_mono.ttf"

/*
 * rendering
 */
static TTF_Font* font;
static SDL_Window *window;
static SDL_Renderer *renderer;
static SDL_Texture *display_buffer;

Sprite *load_sprite(const char *path) {

	Sprite *sprite = malloc(sizeof(Sprite));

	sprite->sdl_texture = IMG_LoadTexture(renderer, path);

	if (!sprite->sdl_texture) {

		printf("Could not load %s (non-fatal error)\n", path);
		sprite->w = 0;
		sprite->h = 0;
		return sprite;
	}

	SDL_QueryTexture(sprite->sdl_texture, NULL, NULL, &sprite->w, &sprite->h);

	return sprite;
}

void draw_sprite(Sprite *sprite, int x, int y, int BOOL_flip) {

	SDL_Rect dst_rect = { x, y, sprite->w, sprite->h };

	SDL_RenderCopyEx(renderer, sprite->sdl_texture, NULL, &dst_rect, 0.0, NULL, BOOL_flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}

void draw_subsprite(Sprite *sprite, int x, int y, int sample_x, int sample_y, int sample_w, int sample_h, int BOOL_flip) {

	SDL_Rect src_rect = { sample_x, sample_y, sample_w, sample_h };
	SDL_Rect dst_rect = { x, y, sample_w, sample_h };

	SDL_RenderCopyEx(renderer, sprite->sdl_texture, &src_rect, &dst_rect, 0.0, NULL, BOOL_flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}

void free_sprite(Sprite *sprite) {
	
	SDL_DestroyTexture(sprite->sdl_texture);
	free(sprite);
}

void draw_text(int x, int y, const char *string) {

	static SDL_Color white = { 255, 255, 255 };

	SDL_Surface* text_surface = TTF_RenderText_Blended(font, string, white);
	SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);

	SDL_Rect text_rect = { x, y };
	TTF_SizeText(font, string, &text_rect.w, &text_rect.h);

	SDL_RenderCopy(renderer, text_texture, NULL, &text_rect);

	SDL_FreeSurface(text_surface);
	SDL_DestroyTexture(text_texture);
}

void draw_text_centered(int x, int y, const char *string) {

	int w;
	TTF_SizeText(font, string, &w, NULL);

	draw_text(x - (w / 2), y, string);
}

/*
 * startpoint
 */
int main() {

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("Error initializing SDL:\n%s\n", SDL_GetError());
		return 1;
	}

	if (TTF_Init() != 0) {
		printf("Error initializing TTF:\n%s\n", TTF_GetError());
		return 1;
	}

	font = TTF_OpenFont(FONT_FILENAME, 24);
	// TTF_CloseFont(font);

	if (!font) {
		printf("Error loading engine font " FONT_FILENAME ".");
		return 1;
	}

	window = SDL_CreateWindow("Feederia", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, DISPLAY_WIDTH, DISPLAY_HEIGHT, SDL_WINDOW_RESIZABLE);

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
	logic_init();

	// process events until window is closed
	SDL_Event event;
	SDL_Rect letterbox = {0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT};

	unsigned long time = 0;
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

			} else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
				
				int x = (event.button.x - letterbox.x) * DISPLAY_WIDTH / letterbox.w;
				int y = (event.button.y - letterbox.y) * DISPLAY_HEIGHT / letterbox.h;

				if (x >= 0 && x < DISPLAY_WIDTH && y >= 0 && y < DISPLAY_HEIGHT)
					logic_click(x, y);
			}
		}

		SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255); 			// clear window to grey
		SDL_RenderClear(renderer);
		SDL_SetRenderTarget(renderer, display_buffer); 				// set render target to display_buffer
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 			// clear display_buffer to black
		SDL_RenderClear(renderer);
		
		logic_tick(time++);											// logic + rendering to display_buffer

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