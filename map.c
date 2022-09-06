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
    if (been_here[hero.z]) {
        panic(9); //panic. we have been here before, so this function should not have been called and continuing may disrupt the game
    }
    int x = 0, y = 0, i_x = 0, i_y = 0, chars = 0, random_int = 0;
    getmaxyx(map, y, x);
    for (i_y = 0; i_y < y; i_y++) {
        for (i_x = 0; i_x < x; i_x++) {
            random_int = roll(1, 1000);
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
            }
        }
    }
    been_here[hero.z] = TRUE;
    return;
}
