/** @file at.c
 *
 * @brief `at` is an outdoor roguelike focused on farming, gathering, and
 *        exploring.
 *
 * This is the main file, not much is defined here, except the `main`
 * function.
 */

/* NOTE: For lack of a better place - at least right now - the mainpage stuff for
 *       Doxygen is here. I might need to find a better place for it once it
 *       becomes too long */
/** @mainpage AT - a roguelike
 *
 * @tableofcontents
 *
 * @section intro Intro
 *
 * AT is a roguelike written in C.
 *
 * @section build Build from source
 *
 * @subsection build-1 Clone the repository
 *
 * Clone the repo to your machine. Make sure you have `make` and `gcc` (or any
 * other C compiler of choice) installed.
 *
 * @subsection build-2 make
 *
 * If you're running Linux, use the command `make linux`. The linux target
 * might work for other *nix OSes, such as *BSD and Darwin. Building on other
 * *nixes than Linux hasn't been tested.
 * If you're running Windows, use the command `make windows`.
 *
 * @subsection make-docs Generate the documentation locally
 *
 * If you plan on hacking on AT, you might want to generate the documentation
 * locally. Run `make docs`, make sure you have `doxygen` installed.
 */

#include <stdlib.h>
#include <locale.h>
#include <curses.h>

#include "cursutils.h"
#include "layout.h"
#include "game.h"

/** @todo `stdio` is only included while testing stuff, remove it when
          done */
#include <stdio.h>

/** @brief The entrypoint for the whole game.
 *  @param argc    The number of cli arguments
 *  @param argv    The value of the cli arguments
 */
int
main (int argc, char *argv[])
{
  setup_curses();

  char intro[][100] = {"Welcome to AT\n",
		       "AT is an outdoor, survival, roguelike-game with a focus on farming.\n",
		       "\n",
		       "TODO: Write a better mini-intro :D\n",
		       "\n",
		       "press [enter] to quit\n"};

  size_t nlines = sizeof(intro) / sizeof(intro[0]);
  vcenter(nlines, stdscr);

  for (size_t i = 0; i < nlines; i++) {
    char *centered_line = center_line(intro[i], stdscr);
    addstr(centered_line);
    free(centered_line);
  }
  box(stdscr, 0, 0);
  refresh();
  getch();

  struct World *world = generate_world();
  if (!world)
    {
      /* Something went wrong! */
      destroy_world(world);
      teardown_curses();
      /* TODO: Bubble up the possible error(s) to this point and show
               a better and more helpful error message! */
      printf("Failed to generate the world!\n");

      return EXIT_FAILURE;
    }

  /* Main game loop */
  /** @todo Eventually move this to its own function */
  bool running = true;

  WINDOW *journal = NULL;
  WINDOW *map = NULL;
  WINDOW *info = NULL;
  setup_layout(&journal, &map, &info);

  while (running)
    {
      /* Show current location in the journal */
      window_box_title (journal, "JOURNAL");
      mvwprintw (journal, 1, 1, "You are at (%ld,%ld)", world->player->creature.coord.x, world->player->creature.coord.y);
      wrefresh (journal);

      /* REFRESH MAP */
      window_box_title (map, "MAP");
      int width, height;
      getmaxyx (map, height, width);

      /* Account for the borders */
      world->map->width = width - 2;
      world->map->height = height - 2;

      mvwprintw (map, 1, 1, "Map dimensions: %dx%d",
		 world->map->width,
		 world->map->height);
      wrefresh (map);
      generate_locations (world);

      for (int x = 0; x < world->map->width; x++)
	{
	  for (int y = 0; y < world->map->height; y++)
	    {
	      struct Coord world_coord = world->map->locations[x][y].coord;
	      struct Coord player_coord = world->player->creature.coord;
	      char tile;
	      if (world_coord.x == player_coord.x && world_coord.y == player_coord.y)
		{
		  tile = '@';
		}
	      else
		{
		  tile = '.';
		}
	      mvwprintw(map, y+1, x+1, "%c", tile);
	      
	    }
	}
      wrefresh (map);
      
      /* COMMAND INTERPRETATION */
      int input = getch();
      switch (input) {
	/* QUIT */
      case 'q':
	/** @todo Implement a "are you sure?" prompt before exiting */
	running = false;
	break;
      case 'h':
	world->player->creature.coord.x -= 1;
	break;
      case 'l':
	world->player->creature.coord.x += 1;
	break;
      case 'j':
	world->player->creature.coord.y += 1;
	break;
      case 'k':
	world->player->creature.coord.y -= 1;
	break;
      case ':':
	window_box_title (info, "PROMPT");
	mvwaddstr (info, 1, 1, "PROMPT mode not implemented yet!");
	wrefresh (info);
	break;
      case '?':
	window_box_title (info, "HELP");
	mvwaddstr (info, 1, 1, "Press '?' for help, 'q' to quit and ':' for command prompt");
	wrefresh (info);
	break;
      default:
	window_box_title (info, "INFO");
	mvwprintw (info, 1, 1, "You inserted the unkown command: %c   ", input);
	wrefresh (info);
	break;
      }
    }

  delwin(journal); delwin(map); delwin(info);
  destroy_world(world);

  teardown_curses();

  return EXIT_SUCCESS;
}
