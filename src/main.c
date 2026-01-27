#include "resloader.h"

int main() {

	Character **characters; // array of character pointers
	int character_count;

	load_resources(&characters, &character_count);

	return 0;
}