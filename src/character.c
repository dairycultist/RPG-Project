#include "window.h"
#include "character.h"

void draw_character(int x, int y, Character *character, int stage, int emotion) {

	draw_subsprite(character->spritesheet, x, y, 512 * emotion, 512 * stage, 512, 512, 0);
}