/**
 * @file game.h
 *
 * @brief Data structures and functions for game entities (game, map,
 *        player, NPCs, ...)
 */

#ifndef AT_GAME
#define AT_GAME

#include <stdlib.h>
#include <stdint.h>

/**
 * @brief A struct describing a creature (player, monsters, NPCs,
 *        animals, ...)
 */
struct Creature {
  /** The creature's name */
  char *name;
  /** The creature single-char representation on the map */
  char icon;
  /** The x coordinate for the creature's current location */
  int64_t x;
  /** The y coordinate for the creature's current location */
  int64_t y;
};

/**
 * @brief A struct describing the player, a kind of Creature
 */
struct Player {
  /** The player is a creature, this field handles everything that's
      common for creatures */
  struct Creature creature;
};

/**
 * @brief Generate the player, setup the struct(s) and allocate the needed memory
 */
struct Player *generate_player();

/**
 * @brief Destroy the player, free the memory allocated by `generate_player`
 *
 * @param player the player to destroy
 */
void destroy_player(struct Player *player);

/**
 * @brief A struct describing the game world
 *
 */
struct World {
  /** The minimum x generated */
  int64_t min_x;
  /** The maximum x generated */
  int64_t max_x;
  /** The minimum y generated */
  int64_t min_y;
  /** The maximum y generated */
  int64_t max_y;
};

#endif
