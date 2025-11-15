/*
 * worldmap scenes are divided into single-screen rooms
 */

typedef struct {

	Sprite *sprite;
	int BOOL_has_collision;

} Tile;
static Tile *tile_registry;
static int tile_registry_size = 256;
static int tile_registry_next = 0;

TileID register_tile(const char *sprite_filepath, int BOOL_has_collision) {

	if (!tile_registry) {

		tile_registry = malloc(sizeof(Tile) * tile_registry_size);

	} else if (tile_registry_next == tile_registry_size) {

		tile_registry_size += 64;
		tile_registry = realloc(sizeof(Tile) * tile_registry_size);

	}

	tile_registry[tile_registry_next].sprite = load_sprite(sprite_filepath);
	tile_registry[tile_registry_next].BOOL_has_collision = BOOL_has_collision;

	return tile_registry_next++;
}

RoomID register_room(TileID tile_ids[ROOM_WIDTH][ROOM_HEIGHT]) {

	return 0;
}

void worldmap_process() {
	
	// draw!
}