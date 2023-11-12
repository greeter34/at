#include <curses.h>
#include "globals.h"

void what_is_here(int area_type) { //known bug - function does not output until player moves
    wprintw(output, "\n%s", tile_descs[area_type]);
    update_windows();
    return;
}

void look() {
    char todo = 0;
    int x = hero.x, y = hero.y, temp_x = 0, temp_y = 0;
    wmove(map, hero.y, hero.x); //put the cursor back to where the hero should be
    curs_set(1);
    while ((todo = wgetch(map)) != 'q') {
        if (todo == 'k') { //move up
            move_cursor(UP);
        }
        if (todo == 'j') { //move down
            move_cursor(DOWN);
        }
        if (todo == 'h') { //move left
            move_cursor(LEFT);
        }
        if (todo == 'l') { //move right
            move_cursor(RIGHT);
        }
        if (todo == 'n') { //move down and right
            move_cursor(DOWNRIGHT);
        }
        if (todo == 'u') { //move up and right
            move_cursor(UPRIGHT);
        }
        if (todo == 'y') { //move up and left
            move_cursor(UPLEFT);
        }
        if (todo == 'b') { //move down and left
            move_cursor(DOWNLEFT);
        };
        if (todo == '.') {
            getyx(map, temp_y, temp_x);
            what_is_here(levels[hero.z][temp_x][temp_y].type);
        }
    }
    curs_set(0);
    hero.x = x;
    hero.y = y;
    return;
}

