#include "cursutils.h"

char *
center_line (char *line, WINDOW *window)
{
  int x = getmaxx(window);

  size_t line_len = strnlen(line, x);

  if (line_len == x)
    {
      return line;
    }

  size_t padding = (x - line_len) / 2;
  size_t final_len = line_len + padding + 1;
  char *output = calloc(1, final_len);

  for (size_t i = 0; i < padding; i++)
    {
      output[i] = ' ';
    }
  strncpy(output + padding, line, line_len);
  return output;
}

void
vcenter (size_t nlines, WINDOW *window)
{
  size_t y = getmaxy(window);

  size_t padding = (y - nlines) / 2;
  for (size_t i = 0; i < padding; i++)
    {
      waddstr(window, "\n");
    }
  return;
}

void
setup_curses ()
{
  setlocale(LC_ALL, "");
  initscr(); cbreak(); noecho();
  curs_set(0);
}

void
teardown_curses ()
{
  curs_set(1); nocbreak(); echo();
  delwin(stdscr);
  endwin();
}
