/**
 * @file at.c
 *
 * @brief `at` is an outdoor roguelike focused on farming, gathering, and
 *        exploring.
 *
 * This is the main file.
 */

#include <stdlib.h>
#include <locale.h>
#include <curses.h>

#include "cursutils.h"

int
main (int argc, char *argv[])
{
  setlocale(LC_ALL, "");
  /* Set up curses */
  initscr(); cbreak(); noecho();
  curs_set(0);

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
  refresh();
  getch();

  /* Tear curses down */
  curs_set(1); nocbreak(); echo();
  delwin(stdscr);
  endwin();
  return EXIT_SUCCESS;
}
