/**
 * @file cursutils.h
 *
 * @brief some utilities built around ncurses.
 *
 */

#ifndef AT_CURSUTILS
#define AT_CURSUTILS

#include <locale.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>

char *center_line(char*, WINDOW*);
void vcenter(size_t, WINDOW*);
void setup_curses();
void teardown_curses();

#endif
