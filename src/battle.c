#include "window.h"
#include "battle.h"
#include "character.h"
#include "modloader.h"

#define FALSE 0
#define TRUE 1

static Sprite *background;
static Sprite *card;
static int time;

static Character **characters;

void battle_init() {

	load_mods(&characters);

	background = load_sprite("src/background.png");
	card = load_sprite("src/card.png");
	time = 0;
}

void battle_tick() {

	time++;
	draw_sprite(background, 0, 0, FALSE);
	draw_subsprite(characters[0]->spritesheet, DISPLAY_WIDTH / 2 - 16, DISPLAY_HEIGHT / 2 - 16, 0, ((time / 4) % 8) * 32, 32, 32, FALSE);
	draw_sprite(card, 0, DISPLAY_HEIGHT - 40, FALSE);
	draw_sprite(card, 80, DISPLAY_HEIGHT - 40, FALSE);
	draw_sprite(card, 160, DISPLAY_HEIGHT - 40, FALSE);
}