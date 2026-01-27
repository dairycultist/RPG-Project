#ifndef RESLOADER_H
#define RESLOADER_H

#define CHARACTER_MAX_NAME_LEN 20

/*
 * resource types
 */

typedef struct {

    char name[CHARACTER_MAX_NAME_LEN];
	// Sprite *spritesheet;

} Character;

typedef struct {

    int display_width, display_height;
	// probably also stuff for input

} HardwareConfig;

void load_resources(Character ***characters, int *character_count);

#endif