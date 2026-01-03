#ifndef CHARACTER_H
#define CHARACTER_H

#define CHARACTER_MAX_NAME_LEN 20

#define EMOTION_DEFAULT 0

typedef struct {

    char name[CHARACTER_MAX_NAME_LEN];
	Sprite *spritesheet;

} Character;

void draw_character(int x, int y, Character *character, int stage, int emotion); // stages go 0-5

#endif