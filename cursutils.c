#include <stdlib.h>
#include <string.h>
#include <curses.h>

#include "cursutils.h"

/**
 * @brief Given a null-terminated LINE, pad it to get centered on the given WINDOW.
 */
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
  char *output = calloc(final_len, 1);

  for (size_t i = 0; i < padding; i++)
    {
      output[i] = ' ';
    }
  strncpy(output + padding, line, line_len);
  return output;
}

/**
 * @brief Given a number of LINES, write the number of padding lines
 * needed for the whole text to be vertically centered in a certain
 * WINDOW.
 */
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
