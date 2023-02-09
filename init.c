#include <curses.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <time.h>
#include "globals.h"

void init_hero() { //initialize hero
    hero.exp = 1;
    hero.x = roll(2, 10);
    hero.y = roll(2, 10);
    hero.z = 0;
    hero.hp = 15;
    hero.max_hp = 12; //deliberately lower than hp for bug testing
    wmove(map, hero.y, hero.x);
    return;
}

void init_tiles() { //initialize types of tiles for the map generator to use
    //these are assigned manually so we can label what the represent in the map generator
    //if applicable the glyph for the tile is added afterwards
    tile_types[0] = 0; //solid rock
    tile_types[1] = 1; //passage way #
    tile_types[2] = 2; //dirt floor
    tile_types[3] = 3; //ice floor
    tile_types[4] = 4; //grass floor
    tile_types[5] = 5; //pool of water
    tile_types[6] = 6; //horizontal wall
    tile_types[7] = 7; //vertical wall
    tile_types[8] = 8; //up stairs
    tile_types[9] = 9; //down stairs
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
