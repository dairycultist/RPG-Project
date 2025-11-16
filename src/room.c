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