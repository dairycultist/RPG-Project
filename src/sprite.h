#ifndef SPRITE_H
#define SPRITE_H

typedef struct {

    void *sdl_texture;
    int w;
    int h;

} Sprite;

void initialize_sprite_handler(SDL_Renderer *r);
Sprite *load_sprite(const char *path);
void draw_sprite(Sprite *sprite, int x, int y, int BOOL_flip);
void draw_subsprite(Sprite *sprite, int x, int y, int sample_x, int sample_y, int sample_w, int sample_h, int BOOL_flip);
void free_sprite(Sprite *sprite);

#endif