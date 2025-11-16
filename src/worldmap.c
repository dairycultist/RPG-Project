static RoomID current_room_id;

static int worldmap_x, worldmap_y; // current position of player's avatar in room

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