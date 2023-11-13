#include "layout.h"

/**
 * @brief: Set up a mock of the final layout, show it, wait for an
 * input and tear down the layout.
 */
void
layout ()
{
  clear();
  refresh();
  int x, y;
  getmaxyx(stdscr, y, x);

  int journal_height = 4;
  int info_height    = 4;
  int map_height     = y - journal_height - info_height;

  WINDOW *journal = newwin(journal_height, x, 0, 0);
  box(journal, 0, 0);
  mvwaddstr(journal, 0, 4, "[JOURNAL]");
  wrefresh(journal);
  WINDOW *map = newwin(map_height, x, journal_height, 0);
  box(map, 0, 0);
  mvwaddstr(map, 0, 4, "[MAP]");
  wrefresh(map);
  WINDOW *info = newwin(info_height, x, y - info_height, 0);
  box(info, 0, 0);
  mvwaddstr(info, 0, 4, "[INFO]");
  wrefresh(info);
  refresh();

  getch();
  delwin(journal); delwin(map); delwin(info);
}
