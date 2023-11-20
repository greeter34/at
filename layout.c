#include "layout.h"

void
setup_layout (WINDOW **journal, WINDOW **map, WINDOW **info)
{
  clear();
  refresh();
  int x, y;
  getmaxyx(stdscr, y, x);

  int journal_height = 7;
  int info_height    = 3;
  int map_height     = y - journal_height - info_height;

  *journal = newwin(journal_height, x, 0, 0);
  window_box_title (*journal, "JOURNAL");
  *map = newwin(map_height, x, journal_height, 0);
  window_box_title (*map, "MAP");
  *info = newwin(info_height, x, y - info_height, 0);
  window_box_title (*info, "INFO");
  /* refresh(); */

}

void
window_box_title (WINDOW *win, char *title)
{
  wclear (win);
  box (win, 0, 0);
  mvwprintw (win, 0, 4, "[%s]", title);
  wrefresh (win);
}
