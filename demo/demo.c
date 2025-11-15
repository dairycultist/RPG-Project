#include <stdio.h>

#include "rpg_project_framework.h"

void init() {

	set_scene(Worldmap);

	// TileID register_tile(const char *sprite_filepath, int BOOL_has_collision);
	// RoomID register_room(TileID tile_ids[ROOM_WIDTH][ROOM_HEIGHT]);
}

void process_event(EventType event_type, void *event_data) {


}