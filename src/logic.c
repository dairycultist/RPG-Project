#include <stdio.h>

#include "window.h"
#include "logic.h"
#include "character.h"
#include "modloader.h"

#define FALSE 0
#define TRUE 1

static Character **characters; // array of character pointers
static int character_count;

static Sprite *waffle_cone;

void logic_init() {

	load_mods(&characters, &character_count);

	waffle_cone = load_sprite("src/waffle_cone.png");
}

void logic_tick(const unsigned long time) {

	// toppings

	draw_character(10, 10, characters[0], (time / 100) % 3, EMOTION_NEUTRAL);

	draw_sprite(waffle_cone, 450, 300, FALSE);

	draw_text(10, 600, "test text!");
}

void logic_click(const int x, const int y) {

	printf("%d %d\n", x, y);
}