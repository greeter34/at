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
                case 6:
                    mvwaddch(map, iterator_y, iterator_x, ACS_VLINE);
                    continue;
                case 7:
                    mvwaddch(map, iterator_y, iterator_x, ACS_HLINE);
                    continue;
                case 10:
                    mvwaddch(map, iterator_y, iterator_x, ACS_ULCORNER);
                    continue;
                case 11:
                    mvwaddch(map, iterator_y, iterator_x, ACS_URCORNER);
                    continue;
                case 12:
                    mvwaddch(map, iterator_y, iterator_x, ACS_LLCORNER);
                    continue;
                case 13:
                    mvwaddch(map, iterator_y, iterator_x, ACS_LRCORNER);
                    continue;
            }
            mvwaddch(map, iterator_y, iterator_x, to_print);
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
    struct Coord {
        int y;
        int x;
    } ul, ur, ll, lr; //four sets of coords representing the corners of a room
    int iterator = 0, x = 0, y = 0, iterator_x = 0, iterator_y = 0, random = 9, rooms_this_level = 1, rooms_made = 0;
    rooms_this_level = (rand() % 4) + 4;
    getmaxyx(map, y, x);
    do {
        ul.x = (rand() % (x - 10)) + 1; //start at least 10 spaces from the bottom of the map
        ul.y = (rand() % (y - 10)) + 1; //start at least 10 spaces from the far right of the map
        ur.x = (ul.x + (roll(1, 5) + 5));
        ur.y = ul.y;
        ll.x = ul.x;
        ll.y = (ul.y + (roll(1, 5) + 5));
        lr.x = ur.x;
        lr.y = ll.y;
        for (iterator = ul.x; iterator < ur.x; iterator++) { //top horizontal wall
            levels[level][iterator][ul.y].walkable = 1;
            levels[level][iterator][ul.y].lit = 1;
            levels[level][iterator][ul.y].type = 7;
        }
        for (iterator = ll.x; iterator < lr.x; iterator++) { //top vertical wall
            levels[level][iterator][ll.y].walkable = 1;
            levels[level][iterator][ll.y].lit = 1;
            levels[level][iterator][ll.y].type = 7;
        }
        for (iterator = ul.y; iterator < ll.y; iterator++) { //left vertical wall
            levels[level][ul.x][iterator].walkable = 1;
            levels[level][ul.x][iterator].lit = 1;
            levels[level][ul.x][iterator].type = 6;
        }
        for (iterator = ur.y; iterator < lr.y; iterator++) { //right vertical wall
            levels[level][ur.x][iterator].walkable = 1;
            levels[level][ur.x][iterator].lit = 1;
            levels[level][ur.x][iterator].type = 6;
        }
        //this sets the tile type as the various corners so they'll display properly on the map
        levels[level][ul.x][ul.y].type = 10;
        levels[level][ur.x][ur.y].type = 11;
        levels[level][ll.x][ll.y].type = 12;
        levels[level][lr.x][lr.y].type = 13;
        rooms_made++;
    } while (rooms_made < rooms_this_level);
    //been_here[hero.z] = TRUE;
    return;
}
