#include "resloader.h"
#include "hardware.h"

int main() {

	// Resources res;
	// load_resources(&res);

	AbstractWindow *window = create_window("Test", 240, 160, 60);
	
	while (1) {
		present(window);
	}

	return 0;
}