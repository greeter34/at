/** @file game.h
 *
 * @brief Data structures and functions for game entities (game, map,
 *        player, NPCs, ...)
 */

#ifndef AT_GAME
#define AT_GAME

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <curses.h>

#include "db.h"

/** @brief A struct representing an (x,y) location */
struct Coord {
  int64_t x, y;
};

/** @brief A struct describing a creature (player, monsters, NPCs,
 *        animals, ...)
 */
struct Creature {
  /** The creature's name
   *  @todo Some creatures might have a dynamically generated name that lives
   *        on the heap and need to be freed, while some others might have a
   *        name coming from a string literal that doesn't need to be freed.
   *        Find a good way to distinguish the two cases. */
  char            *name;
  /** The creature single-char representation on the map */
  char            icon;
  struct Coord    coord;
};

/** @brief A struct describing the player, a kind of Creature */
struct Player {
  /** The player is a creature, this field handles everything that's
      common for creatures */
  struct Creature creature;
};

/** @brief Generate the player, setup the struct(s) and allocate the needed memory */
struct Player *generate_player();

/** @brief Destroy the player, free the memory allocated by `generate_player`
 *
 * @param player the player to destroy
 */
void destroy_player(struct Player *player);

/** @brief A struct describing a location on the map */
struct Location {
  struct Coord coord;
  uint8_t      attributes;      /* Attributes (bit field):
				 * - 2^0:
				 * - 2^1:
				 * - 2^2:
				 * - 2^3:
				 * - 2^4:
				 * - 2^5:
				 * - 2^6:
				 * - 2^7:
				 */
};

/** @brief A struct describing the visible map
 */
struct Map {
  uint16_t          width;         /* The current width of the map */
  uint16_t          height;        /* The current height of the map */
  struct Location **locations;     /* Locations array, kept up-to-date to
                                      store x*y locations with (x + (y*x))
                                      offset */
  bool              dirty;	   /* Wether we need to re-calculate stuff */
};

/** @brief Generate a new Map
 *
 * The generated map will have 0 width and 0 height, and the locations
 * field will be NULL.
 */
struct Map *generate_map();

/** @brief Free the memory for a map
 *
 * @param map a pointer to the map to destroy
 */
void destroy_map(struct Map *map);

/** @brief A struct describing the visible game world
 *
 * This struct only contains the visible part of the map, as well as a
 * reference to the player.
 */

struct World {
  struct Player *player;
  struct Map    *map;
  sqlite3       *db;
};

/** @brief Generate a new world
 *
 * This returns either a pointer to the newly generated world, or NULL
 * in case of error
 */
struct World *generate_world ();

/** @brief Free up the memory used by a world
 *
 *  @param world the world to free
 */
void destroy_world(struct World *world);

/** @brief Generate the visible locations, if needed */
void generate_locations (struct World *world);

#endif
