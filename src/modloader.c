#import <stdio.h>
#import <stdlib.h>

#import "window.h"
#import "character.h"

/*
 * Searches recursively through /mod for game assets.
 * - Text files contain data detailing characters, items, attacks, etc
 * - Images are sprites which are referenced by text files
 *
 * Mods can be conveniently organized into a folder with all their assets
 * together, and may separate data into multiple text files if desired.
 */

void load_mods(Character ***characters) {

	*characters = malloc(sizeof(Character *) * 8);

	(*characters)[0] = malloc(sizeof(Character));
	(*characters)[0]->spritesheet = load_sprite("mod/snivy.png");

	printf("Loaded:\n");
	printf("  Characters:\n");
	printf("    - Snivy\n");

}