#ifndef WINDOW_H
#define WINDOW_H

typedef struct {

    void *sdl_texture;
    int w;
    int h;

} Sprite;

// screen size of GBA; PMD uses 32x32 though many characters mostly fit into 24x24
#define DISPLAY_WIDTH 240
#define DISPLAY_HEIGHT 160

Sprite *load_sprite(const char *path);
void draw_sprite(Sprite *sprite, int x, int y, int BOOL_flip);
void draw_subsprite(Sprite *sprite, int x, int y, int sample_x, int sample_y, int sample_w, int sample_h, int BOOL_flip);
void free_sprite(Sprite *sprite);

#endif