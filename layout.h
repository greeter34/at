/** @file layout.h
 * @brief utilities for the TUI layout of the game (curses windows).
 */
#ifndef AT_LAYOUT
#define AT_LAYOUT

#include <curses.h>

/** @brief Set up a mock of the final layout, show it, wait for an
 * input and tear down the layout.
 *
 *  @param journal The journal window, set by the function
 *
 *  @param map The map window, set by the function
 *
 *  @param info The info window, set by the function
 *
 */
/** @todo Settle on a layout setup for the game
 */
void setup_layout (WINDOW **journal, WINDOW** map, WINDOW** info);

/** @brief Clear a window, draw the border around it, and add a [TITLE] tag to 0,4
 *
 *  @param win the window to act on
 *
 *  @param title the title to print
 */
void window_box_title (WINDOW *win, char *title);

#endif
