#include <stdio.h>

#include "rpg_project_framework.h"

void init() {

	set_scene(Worldmap);

	register_tile("floor.png", 0);

	// RoomID register_room(TileID tile_ids[ROOM_WIDTH][ROOM_HEIGHT]);
}

void process_event(EventType event_type, void *event_data) {


}