/*
 * Searches recursively through /mod for game assets.
 * - Text files contain data detailing characters, items, attacks, etc
 * - Images are sprites which are referenced by text files
 *
 * Mods can be conveniently organized into a folder with all their assets
 * together, and may separate data into multiple text files if desired.
 */

#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "window.h"
#include "character.h"

static Character **c;
static int c_count;

static int file_callback(const char *fpath, const struct stat *sb, int type, struct FTW *ftwbuf) {

	if (type != FTW_F)
		return 0;

	printf("> %s\n", fpath + ftwbuf->base);

	c[c_count] = malloc(sizeof(Character));
	c[c_count]->spritesheet = load_sprite("mod/snivy.png");
	memcpy(c[c_count]->name, "Snivy", 6);
	c_count++;

	return 0;
}

void load_mods(Character ***characters, int *character_count) {

	*characters = malloc(sizeof(Character *) * 8);

	// prep static buffers
	c = *characters;
	c_count = 0;

	// process mod files
	if (nftw("./mod/", file_callback, 4, FTW_CHDIR)) {

		printf("Something went wrong during loading!\n");

	} else {

		printf("Loaded:\n");
		printf("  Characters (%d):\n", c_count);
		
		for (int i = 0; i < c_count; i++)
			printf("    - %s\n", c[i]->name);
	}

	// populate output parameters
	*characters = c;
	*character_count = c_count;

	// clear static buffers
	c = NULL;
}