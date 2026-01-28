#ifndef RESLOADER_H
#define RESLOADER_H

#include "hardware.h"

#define CHARACTER_MAX_NAME_LEN 20

/*
 * resource types
 */
typedef struct {

    char name[CHARACTER_MAX_NAME_LEN];
	AbstractSprite *spritesheet;

} Character;

/*
 * resource wrapper
 */
typedef struct {

    int display_width, display_height;
	// probably also stuff for input

	Character **characters; // array of character pointers
	int character_count;

} Resources;

void load_resources(AbstractWindow *abstract_window, Resources *resources);

#endif