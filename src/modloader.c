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

#include "window.h"
#include "character.h"

static int file_callback(const char *fpath, const struct stat *sb, int tflag, struct FTW *ftwbuf) {

	if (tflag != FTW_F)
		return 0;

	printf("> %s\n", fpath + ftwbuf->base);
	return 0;
}

void load_mods(Character ***characters) {

	*characters = malloc(sizeof(Character *) * 8);

	(*characters)[0] = malloc(sizeof(Character));
	(*characters)[0]->spritesheet = load_sprite("mod/snivy.png");

	printf("Loaded:\n");
	printf("  Characters:\n");
	printf("    - Snivy\n");



	if (nftw("./mod/", file_callback, 4, FTW_CHDIR)) {

		printf("Something went wrong during loading!\n");
	}
}