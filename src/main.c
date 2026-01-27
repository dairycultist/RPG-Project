#include "resloader.h"
#include "hardware.h"

int main() {

	// Resources res;
	// load_resources(&res);

	AbstractWindow *window = create_window("Test", 240, 160, 60);

	AbstractSprite *sprite = load_sprite(window, "./res/card.png");
	
	while (1) {
		draw_sprite(window, sprite, 0, 0, 0);
		present(window);
	}

	return 0;
}