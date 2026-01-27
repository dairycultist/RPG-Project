#include "resloader.h"

int main() {

	HardwareConfig hardware_config = { 100, 100 };
	
	Character **characters; // array of character pointers
	int character_count;

	load_resources(&hardware_config, &characters, &character_count);

	return 0;
}