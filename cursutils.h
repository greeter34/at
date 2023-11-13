/**
 * @file cursutils.h
 *
 * @brief some utilities built around ncurses.
 *
 */

#ifndef AT_CURSUTILS
#define AT_CURSUTILS

#include <curses.h>
#include <stdbool.h>
#include <stdlib.h>

char *center_line(char*, WINDOW*);

void vcenter(size_t, WINDOW*);

#endif
