#include "window.h"
#include "battle.h"

#define FALSE 0
#define TRUE 1

static Sprite *background;
static Sprite *snivy;
static Sprite *card;
static int snivy_i;

// to start, lets just get a character rendering and controllable (reading ALL data externally)

void battle_init() {

	background = load_sprite("src/background.png");
	snivy = load_sprite("src/Idle-Anim.png");
	card = load_sprite("src/card.png");
	snivy_i = 0;
}

void battle_tick() {

	snivy_i++;
	draw_sprite(background, 0, 0, FALSE);
	draw_subsprite(snivy, DISPLAY_WIDTH / 2 - 16, DISPLAY_HEIGHT / 2 - 16, 0, ((snivy_i / 4) % 8) * 32, 32, 32, FALSE);
	draw_sprite(card, 0, DISPLAY_HEIGHT - 40, FALSE);
	draw_sprite(card, 80, DISPLAY_HEIGHT - 40, FALSE);
	draw_sprite(card, 160, DISPLAY_HEIGHT - 40, FALSE);
}