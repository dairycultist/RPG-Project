#include "resloader.h"

int main() {

	AbstractWindow *window = create_window("Test", 240, 160, 60);

	Resources res;
	load_resources(window, &res);

	// AbstractSprite *sprite = load_sprite(window, "./res/snivy.png");
	
	// int t = 0;

	// while (1) {
	// 	draw_subsprite(window, sprite, 0, 0, (t / 8 % 4) * 32, (t / 32 % 8) * 32, 32, 32, 0);
	// 	present(window);
	// 	t++;
	// }

	return 0;
}