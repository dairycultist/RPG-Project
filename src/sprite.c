#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "sprite.h"

static SDL_Renderer *renderer;

void initialize_sprite_handler(SDL_Renderer *r) {

	renderer = r;
}

Sprite *load_sprite(const char *path) {

	Sprite *sprite = malloc(sizeof(Sprite));

	sprite->sdl_texture = IMG_LoadTexture(renderer, path);

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