#ifndef RESLOADER_H
#define RESLOADER_H

#define CHARACTER_MAX_NAME_LEN 20

/*
 * resource types
 */

typedef struct {

    int display_width, display_height;
	// probably also stuff for input

} HardwareConfig;

typedef struct {

    char name[CHARACTER_MAX_NAME_LEN];
	// Sprite *spritesheet;

} Character;

void load_resources(HardwareConfig *hardware_config, Character ***characters, int *character_count);

#endif