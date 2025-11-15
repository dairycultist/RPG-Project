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

/*
 * the worldmap is divided into single-screen rooms
 */

typedef struct {

	TileID tile_ids[ROOM_WIDTH][ROOM_HEIGHT];

} Room;

static Room *room_registry;
static int room_registry_size = 32;
static int room_registry_next = 0;

RoomID register_room(TileID tile_ids[ROOM_WIDTH][ROOM_HEIGHT]) {

	if (!room_registry) {

		room_registry = malloc(sizeof(Room) * room_registry_size);

	} else if (room_registry_next == room_registry_size) {

		room_registry_size += 64;
		room_registry = realloc(room_registry, sizeof(Room) * room_registry_size);

	}

	memcpy(room_registry[room_registry_next].tile_ids, tile_ids, sizeof(TileID[ROOM_WIDTH][ROOM_HEIGHT]));

	return room_registry_next++;
}

RoomID register_room_rowcol(TileID tile_ids_rowcol[ROOM_HEIGHT][ROOM_WIDTH]) {

	TileID tile_ids[ROOM_WIDTH][ROOM_HEIGHT];

	for (int x = 0; x < ROOM_WIDTH; x++)
		for (int y = 0; y < ROOM_HEIGHT; y++)
			tile_ids[x][y] = tile_ids_rowcol[y][x];
	
	return register_room(tile_ids);
}

/*
 * process scene
 */
static RoomID current_room_id;

static int	worldmap_x = DISPLAY_WIDTH / 2,
			worldmap_y = DISPLAY_HEIGHT / 2; // current position of player in room

void set_room(RoomID room_id) {
	
	current_room_id = room_id;
}

void worldmap_process() {
	
	// draw the current room
	Room *current_room = &room_registry[current_room_id];

	for (int x = 0; x < ROOM_WIDTH; x++)
		for (int y = 0; y < ROOM_HEIGHT; y++)
			draw_sprite(tile_registry[current_room->tile_ids[x][y]].sprite, x * TILE_SIZE, y * TILE_SIZE, FALSE);
}