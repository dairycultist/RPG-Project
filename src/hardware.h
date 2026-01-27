#ifndef HARDWARE_H
#define HARDWARE_H

typedef struct {

    void *sdl_texture;
    int w;
    int h;

} Sprite;

typedef void AbstractWindow;

AbstractWindow *create_window(const char *title, int w, int h, int fps);
void present(AbstractWindow *abstract_window);
void destroy_window(AbstractWindow *abstract_window);

// Sprite *load_sprite(const char *path);
// void draw_sprite(Sprite *sprite, int x, int y, int BOOL_flip);
// void draw_subsprite(Sprite *sprite, int x, int y, int sample_x, int sample_y, int sample_w, int sample_h, int BOOL_flip);
// void free_sprite(Sprite *sprite);

#endif