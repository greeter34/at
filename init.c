#include <curses.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <time.h>
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

void init_hero() { //initialize hero
    hero.exp = 1;
    hero.gold = 0;
    hero.x = roll(2, 10);
    hero.y = roll(2, 10);
    hero.z = 0;
    hero.hp = 15;
    hero.max_hp = 12; //deliberately lower than hp for bug testing
    wmove(map, hero.y, hero.x);
    return;
}

void init_game() { //initialize game variables
    int i = 0;
    turns = 0;
    ttl_objects = 0;
    ttl_monsters = 0;
    valid = false;
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
        been_here[i] = false;
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
