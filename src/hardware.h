#ifndef HARDWARE_H
#define HARDWARE_H

typedef void AbstractSprite;
typedef void AbstractWindow;

AbstractWindow *create_window(const char *title, int w, int h, int fps);
void present(AbstractWindow *abstract_window);
void destroy_window(AbstractWindow *abstract_window);

AbstractSprite *load_sprite(AbstractWindow *abstract_window, const char *path);
void draw_sprite(AbstractWindow *abstract_window, AbstractSprite *abstract_sprite, int x, int y, int BOOL_flip);
void draw_subsprite(AbstractWindow *abstract_window, AbstractSprite *abstract_sprite, int x, int y, int sample_x, int sample_y, int sample_w, int sample_h, int BOOL_flip);
void free_sprite(AbstractWindow *abstract_window, AbstractSprite *abstract_sprite);

#endif