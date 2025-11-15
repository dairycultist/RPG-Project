#ifndef FRAMEWORK_H
#define FRAMEWORK_H

// let's start simple ok, not every feature needs to be possible

/*
 * framework-side implemented
 */

// fire_event

// queue_dialogue

// register_character / spritesheet (map, battle, portrait), health, name, etc => id / used for party members, NPCs, and enemies
// register_tile / sprite, has_collision => id
// register_room / tiles[][] => id

/*
 * game-side implemented
 */

// process_event / the framework fires events for the implementer to handle, e.g. when you interact with something in the worldmap, when walk off the edge of a room, etc
// init / runs once at the very start of a save being loaded

#endif