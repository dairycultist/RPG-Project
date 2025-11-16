/*
 * worldmap rooms are composed of tiles
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
		tile_registry = realloc(tile_registry, sizeof(Tile) * tile_registry_size);

	}

	tile_registry[tile_registry_next].sprite = load_sprite(sprite_filepath);
	tile_registry[tile_registry_next].BOOL_has_collision = BOOL_has_collision;

	if (tile_registry[tile_registry_next].sprite->w != TILE_SIZE || tile_registry[tile_registry_next].sprite->h != TILE_SIZE) {

		printf("Error registering tile: \"%s\" is not %dx%d!\n", sprite_filepath, TILE_SIZE, TILE_SIZE);
		exit(1);
	}

	return tile_registry_next++;
}