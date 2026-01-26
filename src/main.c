#include "modloader.h"

int main() {

	Character **characters; // array of character pointers
	int character_count;

	load_mods(&characters, &character_count);

	return 0;
}