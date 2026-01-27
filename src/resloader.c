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

// includes null terminator
#define MAX_LINE_LENGTH 80

#define MAX_CHARACTERS 8

#define HAS_PREFIX(str, prefix) (!strncmp(str, prefix, strlen(prefix)))

static void parse_hardware_config(FILE *file) {

	char line[MAX_LINE_LENGTH];

	while (fgets(line, MAX_LINE_LENGTH, file) && !HAS_PREFIX(line, "#end")) {

		line[strlen(line) - 1] = '\0'; // remove \n

		if (HAS_PREFIX(line, "w=")) {

			sscanf(line + 2, "%d", &r->display_width);

		} else if (HAS_PREFIX(line, "h=")) {

			sscanf(line + 2, "%d", &r->display_height);
		}
	}
}

static Character *parse_character(FILE *file) {

	Character *character = malloc(sizeof(Character));

	char line[MAX_LINE_LENGTH];

	// parse out parameters, ignoring invalid lines, until #end
	while (fgets(line, MAX_LINE_LENGTH, file) && !HAS_PREFIX(line, "#end")) {

		line[strlen(line) - 1] = '\0'; // remove \n

		if (HAS_PREFIX(line, "name=")) {

			memcpy(character->name, line + strlen("name="), strlen(line + strlen("name=")));

		} else if (HAS_PREFIX(line, "spritesheet=")) {

			// character->spritesheet = load_sprite(line + strlen("spritesheet="));
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
	char header[MAX_LINE_LENGTH];

	while (fgets(header, MAX_LINE_LENGTH, file)) {

		if (HAS_PREFIX(header, "#hardware_config"))
			parse_hardware_config(file);

		if (HAS_PREFIX(header, "#character"))
			r->characters[r->character_count++] = parse_character(file);
	}

	// close file
	fclose(file);

	return 0;
}

void load_resources(Resources *resources) {

	// initialize output parameter
	resources->display_width = 100;
	resources->display_height = 100;
	resources->characters = malloc(sizeof(Character *) * MAX_CHARACTERS);
	resources->character_count = 0;

	// prep static reference
	r = resources;

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

	// clear static reference
	r = NULL;
}