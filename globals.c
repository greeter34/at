#include "globals.h"

long unsigned int turns, seed, ttl_objects, ttl_monsters;
WINDOW *stats, *map, *output, *stats_border, *map_border, *output_border;
bool valid;

//char maps[FLOORS][MAP_MAX_X][MAP_MAX_Y];
bool been_here[50];
char tile_types[TTL_TILES];
char tile_descs[TTL_TILES][50];



tile levels[ROOMS][MAP_MAX_X][MAP_MAX_Y];
monster hero;
object *objects;
inventory items[52];
GameTime g_time;
