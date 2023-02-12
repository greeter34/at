#include <curses.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <time.h>
#include "globals.h"

void init_hero() { //initialize hero
    int x = 0, y = 0;
    getmaxyx(map, y, x);
    hero.exp = 1;
    do {
        hero.x = roll(1, x);
        hero.y = roll(1, y);
        hero.z = 0;
    } while (levels[hero.z][hero.x][hero.y].walkable != 1);
    hero.hp = 15;
    hero.max_hp = 12; //deliberately lower than hp for bug testing
    wmove(map, hero.y, hero.x);
    return;
}

void initialize_color() { //initialize color pairings and definitions
    init_pair(1, COLOR_WHITE, COLOR_BLACK); //default color state for the game
    init_pair(2, COLOR_YELLOW, COLOR_BLACK); //dirt floor, doors. should be brown ish
    init_pair(3, COLOR_CYAN, COLOR_BLACK); //ice
    init_pair(4, COLOR_GREEN, COLOR_BLACK); //grass floor, trees
    init_pair(5, COLOR_BLUE, COLOR_BLACK); //water, fountains
    return;
}

void init_tiles() { //initialize types of tiles for the map generator to use
    //these are assigned manually so we can label what the represent in the map generator
    //if applicable the glyph for the tile is added afterwards
    tile_types[0] = ' '; //solid rock
    tile_types[1] = '#'; //passage way #
    tile_types[2] = '.'; //dirt floor
    tile_types[3] = '.'; //ice floor
    tile_types[4] = '.'; //grass floor
    tile_types[5] = '{'; //pool of water
    tile_types[6] = ACS_VLINE; //vertical wall
    tile_types[7] = ACS_HLINE; //horizontal wall
    tile_types[8] = '<'; //up stairs
    tile_types[9] = '>'; //down stairs
    tile_types[10] = ACS_ULCORNER; //upper left corner
    tile_types[11] = ACS_URCORNER; //upper right corner
    tile_types[12] = ACS_LLCORNER; //lower left corner
    tile_types[13] = ACS_LRCORNER; //lower right corner
    return;
}

void init_game() { //initialize game variables
    int i = 0;
    turns = 0;
    ttl_objects = 0;
    ttl_monsters = 0;
    valid = FALSE;
    seed = time(NULL);
    srand(seed);
    initscr();
    cbreak();
    noecho();
    clearok(output, TRUE);
    scrollok(output, TRUE);
    scrollok(map, FALSE);
    scrollok(stats, FALSE);
    curs_set(0);
    if (has_colors() == FALSE) {
        panic(1);
    }
    start_color();
    srand(time(NULL));
    init_windows();
    init_hero();
    initialize_color();
    init_tiles();
    for (i = 0; i < 50; i++) {
        been_here[i] = FALSE;
    }
    update_windows();
    return;
}

void quit() { //attempt to close the program gracefully at the user's request. the graceful stuff is not coded yet though
    if (wprintw(output, "\nThank you for playing. Press any key to quit...") == ERR) panic(4);
    update_windows();
    getch();
    if (endwin() == ERR) panic(5);
    exit(EXIT_SUCCESS);
    return; //this should never be called
}
