#include <curses.h>
#include "globals.h"

void draw_map(int level) {
    wattroff(map, A_REVERSE);
    int i_x = 0, i_y = 0, x = 0, y = 0;
    getmaxyx(map, y, x);
    wmove(map, 0, 0);
    for (i_y = 0; i_y < y; i_y++) {
        for (i_x = 0; i_x < x; i_x++) {
            /* Walls will be implemented as follows:                                     *
             * 1: Vertical line/wall                                                     *
             * 2: Horizontal line/wall                                                   *
             * 3: Upper left corner of wall                                              *
             * 4: Upper right corner of wall                                             *
             * 5: Lower left corner of wall                                              *
             * 6: Lower right corner of wall                                             *
             */
            if (maps[hero.z][i_x][i_y] == '1') {
                waddch(map, ACS_VLINE);
            }
            else if (maps[hero.z][i_x][i_y] == '2') {
                waddch(map, ACS_HLINE);
            }
            else if (maps[hero.z][i_x][i_y] == '3') {
                waddch(map, ACS_ULCORNER);
            }
            else if (maps[hero.z][i_x][i_y] == '4') {
                waddch(map, ACS_URCORNER);
            }
            else if (maps[hero.z][i_x][i_y] == '5') {
                waddch(map, ACS_LLCORNER);
            }
            else if (maps[hero.z][i_x][i_y] == '6') {
                waddch(map, ACS_LRCORNER);
            }
            else {
                wprintw(map, "%c", maps[hero.z][i_x][i_y]);
            }
            //waddch(map, ACS_VLINE);
        }
    }
    wattron(map, A_REVERSE);
    return;
}

void draw_objects(int level) {
    init_color(COLOR_YELLOW, 1000, 1000, 0);
    init_pair(2, COLOR_BLACK, COLOR_YELLOW);
    init_pair(3, COLOR_BLACK, COLOR_BLUE);
    int i = 0;
    for (i = 0; i < ttl_objects; i++) {
        if (objects[i].z == level) {
            wmove(map, objects[i].y, objects[i].x);
            if (objects[i].glyph == '$') {
                wattron(map, COLOR_PAIR(2));
                wprintw(map, "%c", objects[i].glyph);
                wattroff(map, COLOR_PAIR(2));
                wrefresh(map);
            }
            else if (objects[i].glyph == '}') {
                wattron(map, COLOR_PAIR(3));
                wprintw(map, "%c", objects[i].glyph);
                wattroff(map, COLOR_PAIR(3));
                wrefresh(map);
            }
        }
    }
    return;
}

void draw_monsters(int level) { //no other monsters, only hero is drawn
    wattron(map, A_REVERSE);
    wmove(map, hero.y, hero.x);
    wprintw(map, "@");
    return;
}

void redraw_screen() { //this function should be called, rather than one of the above ones directly
    draw_map(hero.z); //always draw the map first. then things can be drawn on top of it
    draw_objects(hero.z);
    draw_monsters(hero.z); //always draw monsters last so that they hide objects they are standing on. also make the player normally visible
    wrefresh(map);
    return;
}

void generate_level () {
    struct Coord {
        unsigned int x;
        unsigned int y;
    };
    if (been_here[hero.z]) {
        panic(9); //panic. we have been here before, so this function should not have been called and continuing may disrupt the game
    }
    int i = 0, x = 0, y = 0, i_x = 0, i_y = 0, wall_length = 0, wall_height = 0;
    struct Coord upper_lc, upper_rc, lower_lc, lower_rc;
    getmaxyx(map, y, x);
    for (i_y = 0; i_y < y; i_y++) {
        for (i_x = 0; i_x < x; i_x++) {
            maps[hero.z][i_x][i_y] = ' '; //blank the map to start
            /*random_int = roll(1, 1000);
            update_windows();
            //following code is proof of concept. i plan extensive rewrites to this
            if (random_int > 300 && random_int < 997) {
                maps[hero.z][i_x][i_y] = '.';
            }
            else if (random_int == 998) {
                create_object(hero.z, i_x, i_y, '}');
                maps[hero.z][i_x][i_y] = '.';
            }
            else if (random_int == 997) {
                maps[hero.z][i_x][i_y] = '#';
            }
            else if (random_int == 999) {
                create_object(hero.z, i_x, i_y, '$');
                maps[hero.z][i_x][i_y] = '.';
            }
            else {
                maps[hero.z][i_x][i_y] = ' ';
            }*/
        }
    }

    //establish room corners
    upper_lc.x = roll(1, (x / 4));
    upper_lc.y = roll(1, (y / 4));
    upper_rc.x = (upper_lc.x + (roll(1, 10) + 3));
    upper_rc.y = upper_lc.y;
    lower_lc.x = upper_lc.x;
    lower_lc.y = (upper_lc.y + (roll(1, 10) + 3));
    lower_rc.x = upper_rc.x;
    lower_rc.y = lower_lc.y;
    //assign room corner values into array
    maps[hero.z][upper_lc.x][upper_lc.y] = '3';
    maps[hero.z][upper_rc.x][upper_rc.y] = '4';
    maps[hero.z][lower_lc.x][lower_lc.y] = '5';
    maps[hero.z][lower_rc.x][lower_rc.y] = '6';
    //fill in horizontal walls
    for (i = (upper_lc.x + 1); i < upper_rc.x; i++) {
        maps[hero.z][i][upper_lc.y] = '2';
        maps[hero.z][i][lower_lc.y] = '2';
    }
    //fill in vertical walls
    for (i = (upper_lc.y + 1); i < lower_lc.y; i++) {
        maps[hero.z][upper_lc.x][i] = '1';
        maps[hero.z][upper_rc.x][i] = '1';
    }
    for (i_y = upper_lc.y; i_y < lower_rc.y; i_y++) {
        for (i_x = upper_lc.x; i_x < upper_rc.x; i_x++) {
            if (maps[hero.z][i_x][i_y] != ' ') {
                continue;
            }
            else {
                maps[hero.z][i_x][i_y] = '.';
            }
        }
    }
    been_here[hero.z] = TRUE;
    return;
}
