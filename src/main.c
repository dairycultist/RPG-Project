#include "resloader.h"

int main() {

	AbstractWindow *window = create_window("Test", 240, 160, 60);

	Resources res;
	load_resources(window, &res);

	int t = 0;

	while (1) {

		for (int i=0; i<res.character_count; i++)
			draw_subsprite(window, res.characters[i]->spritesheet, i * 32, 0, (t / 8 % 4) * 32, (t / 32 % 8) * 32, 32, 32, 0);
		present(window);
		t++;
	}

	return 0;
}