#include <curses.h>
#include <stdlib.h>
#include <stdlib.h>
#include "globals.h"

void draw_map(int level) {
    char to_print = ' ';
    int attributes = 5, iterator = 1, iterator_x = 0, iterator_y = 0, x = 0, y = 0;
    wattroff(map, A_REVERSE);
    getmaxyx(map, y, x);
    wmove(map, 0, 0);
    for (iterator_y = 0; iterator_y < y; iterator_y++) {
        for (iterator_x = 0; iterator_x < x; iterator_x++) {
            to_print = tile_types[levels[level][iterator_x][iterator_y].type];
            switch(levels[level][iterator_x][iterator_y].type) {
                case 2:
                    wattron(map, COLOR_PAIR(2));
                    break;
                case 3:
                    wattron(map, COLOR_PAIR(3));
                    break;
                case 4:
                    wattron(map, COLOR_PAIR(4));
                    break;
                case 5:
                    wattron(map, COLOR_PAIR(5));
                    break;
            }
            mvwprintw(map, iterator_y, iterator_x, "%c", to_print);
            wattron(map, COLOR_PAIR(1));
            wattroff(map, A_REVERSE);
            wattroff(map, A_BOLD);
        }
    }
    wattron(map, A_REVERSE);
    return;
}

void draw_objects(int level) {
    int i = 0;
    for (i = 0; i < ttl_objects; i++) {
        if (objects[i].z == level) {
            wmove(map, objects[i].y, objects[i].x);
            if (objects[i].glyph == '}') {
                wattron(map, COLOR_PAIR(5));
                wprintw(map, "%c", objects[i].glyph);
                wattroff(map, COLOR_PAIR(5));
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

void generate_level(int level) {
    if (been_here[hero.z]) {
        panic(9); //panic. we have been here before, so this function should not have been called and continuing may disrupt the game
    }
    int x = 0, y = 0, iterator_x = 0, iterator_y = 0, random = 9;
    getmaxyx(map, y, x);
    for (iterator_y = 0; iterator_y < y; iterator_y++) {
        for (iterator_x = 0; iterator_x < x; iterator_x++) {
            random = (rand() % 10);
            levels[level][iterator_x][iterator_y].type = random; //this is not a good map gen
        }
    }
    //been_here[hero.z] = TRUE;
    return;
}
