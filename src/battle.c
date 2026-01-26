#include "window.h"
#include "battle.h"
#include "character.h"
#include "modloader.h"

#define FALSE 0
#define TRUE 1

static Sprite *background;
static Sprite *card;
static int time;

static Character **characters; // array of character pointers
static int character_count;

void battle_init() {

	load_mods(&characters, &character_count);

	background = load_sprite("src/background.png");
	card = load_sprite("src/card.png");
	time = 0;
}

void battle_tick() {

	time++;
	draw_sprite(background, 0, 0, FALSE);
	draw_subsprite(characters[0]->spritesheet, 182, 30, 0, ((time / 4) % 8) * 32, 32, 32, FALSE);
	draw_subsprite(characters[1]->spritesheet, 182, 51, 0, ((time / 4) % 8) * 32, 32, 32, FALSE);
	
	draw_sprite(card, 0, DISPLAY_HEIGHT - 40, FALSE);
}