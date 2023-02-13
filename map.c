#include <curses.h>
#include <stdlib.h>
#include <stdlib.h>
#include "globals.h"

void draw_map(int level) {
    char to_print = ' ';
    int iterator_x = 0, iterator_y = 0, x = 0, y = 0;
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

bool generate_level(int level) {
    if (been_here[hero.z]) {
        panic(9); //panic. we have been here before, so this function should not have been called and continuing may disrupt the game
    }
    struct Coord {
        int y;
        int x;
    } ul, ur, ll, lr; //four sets of coords representing the corners of a room
    int iterator = 0, x = 0, y = 0, iterator_x = 0, iterator_y = 0, rooms_this_level = 1, rooms_made = 0, counter = 0;
    bool success = false;
    rooms_this_level = (rand() % 6) + 4;
    getmaxyx(map, y, x);
    do {
        bool room_here = false;
        if (counter > 10000) break; //if we've tried ten thousand times with these parameters to generate a map unsuccessfully, we better bail
        ul.x = (roll(1, x) - 5); //start at least 5 spaces from the far right of the draw_map
        ul.y = (roll(1, y) - 5); //start at least 5 spaces from the bottom of the map
        ur.x = (ul.x + (roll(1, 10) + 3)); //rooms are between 3 and 13 nodes wide
        ur.y = ul.y;
        ll.x = ul.x;
        ll.y = (ul.y + (roll(1, 10) + 3)); //rooms are between 3 and 13 nodes high
        lr.x = ur.x;
        lr.y = ll.y;
        if ((lr.x > (x - 1)) || (lr.y > (y - 1)) || (ul.x < 1) || (ul.y < 1)) {
            counter++;
            continue; //try again if rooms exceed map boundaries
        }
        //scan the area to ensure a room is not already here
        for (iterator_y = (ul.y - 1); iterator_y < (lr.y + 1); iterator_y++) {
            for (iterator_x = (ul.x - 1); iterator_x < (lr.x + 1); iterator_x++) {
                if (levels[level][iterator_x][iterator_y].type != 0) room_here = true;
            }
        }
        if (room_here) {
            counter++;
            continue; //try again if room would be stacked over existing room
        }
        for (iterator = ul.x; iterator < ur.x; iterator++) { //top horizontal wall
            levels[level][iterator][ul.y].walkable = 0;
            levels[level][iterator][ul.y].lit = 1;
            levels[level][iterator][ul.y].type = 7;
        }
        for (iterator = ll.x; iterator < lr.x; iterator++) { //top vertical wall
            levels[level][iterator][ll.y].walkable = 0;
            levels[level][iterator][ll.y].lit = 1;
            levels[level][iterator][ll.y].type = 7;
        }
        for (iterator = ul.y; iterator < ll.y; iterator++) { //left vertical wall
            levels[level][ul.x][iterator].walkable = 0;
            levels[level][ul.x][iterator].lit = 1;
            levels[level][ul.x][iterator].type = 6;
        }
        for (iterator = ur.y; iterator < lr.y; iterator++) { //right vertical wall
            levels[level][ur.x][iterator].walkable = 0;
            levels[level][ur.x][iterator].lit = 1;
            levels[level][ur.x][iterator].type = 6;
        }
        //this sets the tile type as the various corners so they'll display properly on the map
        levels[level][ul.x][ul.y].type = 10;
        levels[level][ur.x][ur.y].type = 11;
        levels[level][ll.x][ll.y].type = 12;
        levels[level][lr.x][lr.y].type = 13;
        //fill the rooms with flooring
        ul.x++;
        ul.y++;
        int random_floor = roll(1, 3) + 1;
        for (iterator_y = ul.y; iterator_y < lr.y; iterator_y++) {
            for (iterator_x = ul.x; iterator_x < lr.x; iterator_x++) {
                levels[level][iterator_x][iterator_y].walkable = 1;
                levels[level][iterator_x][iterator_y].lit = 1;
                levels[level][iterator_x][iterator_y].type = random_floor;
            }
        }
        rooms_made++;
        if (rooms_made == rooms_this_level) success = true;
    } while (rooms_made < rooms_this_level);
    //been_here[hero.z] = TRUE;
    return success;
}
