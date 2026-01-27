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

/*
 * resource wrapper
 */
typedef struct {

    int display_width, display_height;
	// probably also stuff for input

	Character **characters; // array of character pointers
	int character_count;

} Resources;

void load_resources(Resources *resources);

#endif