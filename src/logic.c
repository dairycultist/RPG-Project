#include "window.h"
#include "logic.h"
#include "character.h"
#include "modloader.h"

#define FALSE 0
#define TRUE 1

static int time;

static Character **characters; // array of character pointers
static int character_count;

void logic_init() {

	load_mods(&characters, &character_count);

	time = 0;
}

void logic_tick() {

	time++;
	draw_subsprite(characters[0]->spritesheet, 10, 10, 0, 0, 512, 512, FALSE);
}