#include <curses.h>
#include "globals.h"

void init_windows() { //create windows for the map, hero stats, and output messages
    int mapx = 0, mapy = 0, i = 0; //used to store maximum width and height of map
    init_color(COLOR_BLACK, 0, 0, 0);
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    if (clear() == ERR) panic(10);
    wattron(map, COLOR_PAIR(1));
    bkgd(COLOR_PAIR(1));
    if ((output = initscr()) == NULL) panic(2);
    if ((map = initscr()) == NULL) panic(2);
    if ((stats = initscr()) == NULL) panic(2);
    if ((output_border = initscr()) == NULL) panic(2);
    if ((map_border = initscr()) == NULL) panic(2);
    if ((stats_border = initscr()) == NULL) panic(2);
    if ((LINES - 13) > MAP_MAX_X) {mapx = MAP_MAX_X;}
    else {mapx = (LINES - 13);}
    if ((COLS - 1) > MAP_MAX_Y) {mapy = MAP_MAX_Y;}
    else {mapy = (COLS - 1);}
    output_border = newwin(6, (COLS - 1), 1, 1);
    map_border = newwin(mapx, mapy, 7, 1);
    stats_border = newwin(4, (COLS - 1), (LINES - 6), 1);
    output = newwin(4, (COLS - 3), 2, 2);
    map = newwin((mapx - 2), (mapy - 2), 8, 2);
    stats = newwin(2, (COLS - 3), (LINES - 5), 2);
    box(output_border, 0, 0);
    box(map_border, 0, 0);
    box(stats_border, 0, 0);
    generate_level(); //this generates only the first level, though the function will be used to generate later levels
    return;
}

void update_windows() {
    static bool called = FALSE;
    if (wnoutrefresh(stdscr) == ERR) panic(3);
    if (wnoutrefresh(curscr) == ERR) panic(3);
    if (wnoutrefresh(stats) == ERR) panic(3);
    if (wnoutrefresh(output) == ERR) panic(3);
    if (wnoutrefresh(map) == ERR) panic(3);
    if (!called) {
        if (wnoutrefresh(output_border) == ERR) panic(4);
        if (wnoutrefresh(stats_border) == ERR) panic(4);
        if (wnoutrefresh(map_border) == ERR) panic(4);
        called = TRUE;
    }
    if (doupdate() == ERR) panic(5);
    return;
}

void fix_windows() { //call this after displaying a temporary window, ie for inventory
    /* The following I feel needs explanation. First we erase the whole screen. Then we touchwin the output *
    * and stats windows. The map we don't care about, as this is stored in an array anyway and reprinted   *
    * as needed. we update the windows to push the inventory screen off of the terminal. Then we box our   *
    * map, output, and stats border windows, and then touchwin again on output and stats. Again with map   *
    * in our array, we do not care if this gets clobbered. We then wrefresh the borders, as by default     *
    * update_windows only refreshes those windows when the game first runs. We then update windows again   *
    * to ensure that the stats and output windows maintain the information originally being displayed      */
    werase(stdscr);
    touchwin(output);
    touchwin(stats);
    update_windows();
    box(output_border, 0, 0);
    touchwin(output);
    box(map_border, 0, 0);
    box(stats_border, 0, 0);
    touchwin(stats);
    wrefresh(output_border);
    wrefresh(map_border);
    wrefresh(stats_border);
    update_windows();
    return;
}
