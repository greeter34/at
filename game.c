#include "game.h"
include "db.h"

struct Player
*generate_player ()
{
  struct Player *player = calloc(1, sizeof(struct Player));
  player->creature.name = "AT";
  player->creature.icon = '@';
  /* Player always spawns at (0,0) */
  player->creature.x = 0;
  player->creature.y = 0;

  return player;
}

void
destroy_player (struct Player *player)
{
  free(player);
}

struct Map
*generate_map ()
{
  struct Map *map = calloc(1, sizeof(struct Map));
  return map;
}

void
destroy_map (struct Map *map)
{
  /* TODO: free the `locations'  as well, if it isn't null. */
  free(map);
}

struct World
*generate_world ()
{
  struct World *world = calloc(1, sizeof(struct World));

  world->map    = generate_map();
  world->player = generate_player();

  world->db     = get_memory_db();
  if (!world->db)
    {
      return NULL;
    }

  return world;
}

void
destroy_world (struct World *world)
{
  destroy_player(world->player);
  destroy_map(world->map);
  sqlite3_close(world->db);

  free(world);
}
