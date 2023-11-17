/** @file cursutils.h
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

/** @brief Given a null-terminated LINE, pad it to get centered on the
 *        given WINDOW.
 *
 * @param line a null-terminated string to be centered
 *
 * @param window the window where `line` will be printed
 */
char *center_line(char* line, WINDOW* window);

/** @brief Given a number of lines, write the number of padding lines
 * needed for the whole text to be vertically centered in a certain
 * window.
 *
 * @param nlines the number of lines to vertically center
 *
 * @param window the window where the lines will be printed
 */
void vcenter(size_t nlines, WINDOW* window);


/** @brief Set up curses
 */
void setup_curses();

/** @brief Clean up curses stuff when exiting
 */
void teardown_curses();

#endif
