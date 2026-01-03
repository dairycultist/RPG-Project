#include <stdio.h>

#include "window.h"
#include "logic.h"
#include "character.h"
#include "modloader.h"

#define FALSE 0
#define TRUE 1

static Character **characters; // array of character pointers
static int character_count;

void logic_init() {

	load_mods(&characters, &character_count);
}

void logic_tick(const unsigned long time) {

	draw_character(10, 10, characters[0], 0, EMOTION_NEUTRAL);
}

void logic_click(const int x, const int y) {

	printf("%d %d\n", x, y);
}