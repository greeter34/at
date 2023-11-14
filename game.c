#include "game.h"

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
