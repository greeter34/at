#include "game.h"
#include "db.h"

struct Player
*generate_player ()
{
  struct Player *player = calloc (1, sizeof (struct Player));
  player->creature.name = "AT";
  player->creature.icon = '@';
  /* Player always spawns at (0,0) */
  player->creature.coord.x = 1;
  player->creature.coord.y = 1;

  return player;
}

void
destroy_player (struct Player *player)
{
  free (player);
}

struct Map
*generate_map ()
{
  struct Map *map = calloc (1, sizeof (struct Map));
  return map;
}

void
destroy_map (struct Map *map)
{
  if (map->locations)
    {
      for (int x = 0; x < map->width; x++)
	{
	      free (map->locations[x]);
	}
      free (map->locations);
    }
  free (map);
}

struct World
*generate_world ()
{
  struct World *world = calloc (1, sizeof (struct World));

  world->map       = generate_map ();
  world->map->dirty = true;
  world->player    = generate_player ();

  world->db        = setup_memory_db ();
  if (!world->db)
    {
      return NULL;
    }

  /** @todo Continue from here! I need to set the map's members to
            generate the right amount of locations. Afterwards, show
            the locations (and the player) on the map window and
            figure out how to refresh the screen and how to react to a
            change of terminal size (which will also require a map
            redraw, and possibly to generate some new locations) */

  generate_locations (world);

  return world;
}

void
destroy_world (struct World *world)
{
  destroy_player (world->player);
  destroy_map (world->map);
  sqlite3_close (world->db);

  free (world);
}

void
generate_locations (struct World *world)
{
  world->map->locations = calloc (world->map->width,
				  sizeof (struct Location *));
  if (!world->map->locations)
    {
      wclear (stdscr);
      waddstr (stdscr, "ERROR WHEN ALLOCATING LOCATIONS ARRAY!");
      wrefresh (stdscr);
      getch();
    }
  for (int x = 0; x < world->map->width; x++)
    {
      world->map->locations[x] = calloc (world->map->height,
					 sizeof (struct Location));
      if (!world->map->locations[x])
	{
	  wclear (stdscr);
	  waddstr (stdscr, "ERROR WHEN ALLOCATING LOCATIONS ARRAY!");
	  wrefresh (stdscr);
	  getch();
	}
    }

  struct Coord min_coord, max_coord;
  struct Coord player_coord = world->player->creature.coord;
  uint16_t width = world->map->width;
  uint16_t height = world->map->height;
  
  min_coord.x = player_coord.x - (width / 2);
  max_coord.x = min_coord.x + width;
  min_coord.y = player_coord.y - (height / 2);
  max_coord.y = min_coord.y + height;

  sqlite3_stmt *stmt;
  int rc;
  char *query;

  query = "SELECT x, y "
    "FROM locations "
    "where x > ? AND x < ? AND y > ? AND y < ?";

  rc = sqlite3_prepare_v2(world->db, query, -1, &stmt, 0);
  if (rc != SQLITE_OK)
    {
      /** @todo Bubble up an error instead! */
      return;
    }

  sqlite3_bind_int64(stmt, 1, (sqlite3_int64) min_coord.x);
  sqlite3_bind_int64(stmt, 2, (sqlite3_int64) max_coord.x);
  sqlite3_bind_int64(stmt, 3, (sqlite3_int64) min_coord.y);
  sqlite3_bind_int64(stmt, 4, (sqlite3_int64) max_coord.y);

  /* A bytemap used to mark the locations present in the db */
  char *locations = calloc(width, height);

  /* Mark all the known locations */
  int step = sqlite3_step (stmt);
  while (step == SQLITE_ROW)
    {
      sqlite3_int64 x = sqlite3_column_int64(stmt, 0);
      sqlite3_int64 y = sqlite3_column_int64 (stmt, 1);

      /* Convert x and y in the world to x and y in the map */
      struct Coord map_coord;
      map_coord.x = x + (width / 2);
      map_coord.y = y + (height / 2);
      locations[map_coord.x + (map_coord.y * map_coord.x)] = 1;

      /* Insert the current location in the locations array in the
       * Map and populate its coord member */
      world->map->locations[map_coord.x][map_coord.y].coord.x = x;
      world->map->locations[map_coord.x][map_coord.y].coord.y = y;
  
      step = sqlite3_step(stmt);
    }
  
  /* Generate all unknown locations */
  sqlite3_exec(world->db, "BEGIN TRANSACTION", NULL, NULL, NULL);
  for (uint64_t x = 0; x < width; x++)
    {
      for (uint64_t y = 0; y < height; y++)
	{
	  if (locations[x + (y * x)] == 0)
	    {
	      /* Convert x and y in the map to x and y in the world */
	      struct Coord world_coord;
	      world_coord.x = x - (width / 2);
	      world_coord.y = y - (height / 2);
	      sqlite3_stmt *insert_stmt;
	      char *insert_query = "INSERT INTO locations (x, y) "
		"VALUES (?, ?)";
	      int res_code = sqlite3_prepare_v2(world->db, insert_query, -1, &insert_stmt, 0);
	      if (res_code != SQLITE_OK)
		{
		  /** @todo Bubble up an error instead! */
		  return;
		}
	      sqlite3_bind_int64 (insert_stmt, 1, (sqlite3_int64) world_coord.x);
	      sqlite3_bind_int64 (insert_stmt, 2, (sqlite3_int64) world_coord.y);

	      sqlite3_step (insert_stmt);
	      sqlite3_finalize (insert_stmt);

	      /* Insert the newly generated location in the locations
	       * array in the Map and populate its coord memeber */
	      world->map->locations[x][y].coord.x = world_coord.x;
	      world->map->locations[x][y].coord.y = world_coord.y;
	    }
	}
    }
  sqlite3_exec(world->db, "END TRANSACTION", NULL, NULL, NULL);
  sqlite3_finalize(stmt);
  free (locations);
}
