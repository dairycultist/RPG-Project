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

// includes null terminator
#define MAX_LINE_LENGTH 80

#define IS_LINE_PREFIXED_WITH(line, prefix) (strncmp(line, prefix, strlen(prefix)) == 0)

static Character *parse_character(FILE *file) {

	Character *character = malloc(sizeof(Character));

	char line[MAX_LINE_LENGTH];

	while (fgets(line, MAX_LINE_LENGTH, file) && !IS_LINE_PREFIXED_WITH(line, "#end")) {

		if (IS_LINE_PREFIXED_WITH(line, "name=")) {

			printf("ONE!\n");

		} else if (IS_LINE_PREFIXED_WITH(line, "spritesheet=")) {

			printf("TWO!\n");
		}

	}

	character->spritesheet = load_sprite("mod/snivy.png");
	memcpy(character->name, "Snivy", 6);

	return character;
}

static int file_callback(const char *fpath, const struct stat *sb, int type, struct FTW *ftwbuf) {

	// only accept files (not folders)
	if (type != FTW_F)
		return 0;

	const char *filename = fpath + ftwbuf->base;
	const char *extension = strrchr(filename, '.');

	// only accept files with the .txt extension
    if (!extension || extension == filename || strcmp(extension, ".txt"))
        return 0;

	// open the file for reading
	FILE *file = fopen(filename, "r");

	if (file == NULL)
		return 0;

	// parse (based on header) until EOF
	char header[MAX_LINE_LENGTH];

	while (fgets(header, MAX_LINE_LENGTH, file)) {

		if (IS_LINE_PREFIXED_WITH(header, "#character")) {

			c[c_count] = parse_character(file);
			c_count++;
		}
	}

	// close file
	fclose(file);

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