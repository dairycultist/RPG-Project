#ifndef FRAMEWORK_H
#define FRAMEWORK_H

// let's start simple ok, not every feature needs to be possible

#define DISPLAY_WIDTH 640
#define DISPLAY_HEIGHT 400
#define ROOM_WIDTH 40
#define ROOM_HEIGHT 25
#define TILE_SIZE 16

typedef enum {

	INTERACT_WITH_TILE

} EventType;

typedef enum { Worldmap, Battle, Shop } Scene;

typedef int CharacterID;
typedef int TileID;
typedef int RoomID;

/*
 * framework-side implemented
 */

// fire_event

// queue_dialogue

// register_character / spritesheet (map, battle, portrait), health, name, etc => id / used for party members, NPCs, and enemies
TileID register_tile(const char *sprite_filepath, int BOOL_has_collision);
RoomID register_room(TileID tile_ids[ROOM_WIDTH][ROOM_HEIGHT]);
RoomID register_room_rowcol(TileID tile_ids_rowcol[ROOM_HEIGHT][ROOM_WIDTH]);

void set_room(RoomID room_id);

void set_scene(Scene scene);

/*
 * game-side implemented
 */

// runs once at the very start of a save being loaded
void init();

// the framework fires events for the implementer to handle, e.g. when you interact with something in the worldmap, when walk off the edge of a room, etc
void process_event(EventType event_type, void *event_data);

#endif