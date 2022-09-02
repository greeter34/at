#include <curses.h>
#include "globals.h"

void draw_map(int level) {
    wattroff(map, A_REVERSE);
    int i_x = 0, i_y = 0, x = 0, y = 0;
    getmaxyx(map, y, x);
    wmove(map, 0, 0);
    for (i_y = 0; i_y < y; i_y++) {
        for (i_x = 0; i_x < x; i_x++) {
            wprintw(map, "%c", maps[hero.z][i_x][i_y]);
        }
        wprintw(map, "\n");
    }
    wattron(map, A_REVERSE);
    return;
}
