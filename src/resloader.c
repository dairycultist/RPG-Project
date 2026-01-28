/*
 * Searches recursively through /res for game assets.
 * - Text file(s) containing data detailing characters, items, actions, rooms, etc
 * - Images are sprites which are referenced by text files
 */

#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "resloader.h"

static Resources *r;
static AbstractWindow *aw;

// includes null terminator
#define MAX_LINE_LENGTH 80

#define MAX_CHARACTERS 8

#define HAS_PREFIX(str, prefix) (!strncmp(str, prefix, strlen(prefix)))

static Character *parse_character(FILE *file) {

	Character *character = malloc(sizeof(Character));

	char line[MAX_LINE_LENGTH];

	// parse out parameters, ignoring invalid lines, until de-indent
	while (fgets(line, MAX_LINE_LENGTH, file) && HAS_PREFIX(line, "\t")) {

		line[strlen(line) - 1] = '\0'; // remove \n

		if (HAS_PREFIX(line, "\tname=")) {

			memcpy(character->name, line + strlen("\tname="), strlen(line + strlen("\tname=")));

		} else if (HAS_PREFIX(line, "\tspritesheet=")) {

			character->spritesheet = load_sprite(aw, line + strlen("\tspritesheet="));
		}
	}

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
	char line[MAX_LINE_LENGTH];

	while (fgets(line, MAX_LINE_LENGTH, file)) {

		if (HAS_PREFIX(line, "width="))
			sscanf(line, "width=%d", &r->display_width);

		else if (HAS_PREFIX(line, "height="))
			sscanf(line, "height=%d", &r->display_height);

		else if (HAS_PREFIX(line, "character:"))
			r->characters[r->character_count++] = parse_character(file);
	}

	// close file
	fclose(file);

	return 0;
}

void load_resources(AbstractWindow *abstract_window, Resources *resources) {

	// initialize output parameter
	resources->display_width = 100;
	resources->display_height = 100;
	resources->characters = malloc(sizeof(Character *) * MAX_CHARACTERS);
	resources->character_count = 0;

	// prep static references
	r = resources;
	aw = abstract_window;

	// process res files
	if (nftw("./res/", file_callback, 4, FTW_CHDIR)) {

		printf("Something went wrong during loading!\n");

	} else {

		printf("Loaded:\n");

		printf("  Hardware config:\n    dim: %dx%d\n", r->display_width, r->display_height);

		printf("  Characters (%d):\n", r->character_count);
		
		for (int i = 0; i < r->character_count; i++)
			printf("    - %s\n", r->characters[i]->name);
	}

	// clear static references
	r = NULL;
	aw = NULL;
}