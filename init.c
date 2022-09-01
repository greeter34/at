#include <curses.h>
#include <stdlib.h>
#include <time.h>
#include "globals.h"

#define MAP_MAX_X 25
#define MAP_MAX_Y 80

void init_windows() { //create windows for the map, hero stats, and output messages
    int mapx = 0, mapy = 0, i = 0; //used to store maximum width and height of map
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
    stats = newwin(3, (COLS - 3), (LINES - 6), 2);
    box(output_border, 0, 0);
    box(map_border, 0, 0);
    box(stats_border, 0, 0);
    for (i = 0; i < 100; i++) {
        wprintw(output, "\n"); //to scroll to bottom of output window
        update_windows();
    }
    for (i = 0; i < 2000; i++) {
        wprintw(map, "."); //fill the map with movable space
        wprintw(output, "\nAdded dot %d", i);
        update_windows();
    }
    return;
}

void init_hero() { //initialize hero
    hero.gold = 0;
    hero.x = 10;
    hero.y = 10;
    hero.hp = 15;
    hero.max_hp = 12; //deliberately lower than hp for bug testing
    wmove(map, hero.y, hero.x);
    wattron(map, A_REVERSE);
    return;
}

void init_game() { //initialize game variables
    turns = 0;
    valid = false;
    initscr();
    cbreak();
    noecho();
    idlok(output, TRUE);
    scrollok(output, TRUE);
    scrollok(map, FALSE);
    scrollok(stats, FALSE);
    curs_set(0);
    start_color();
    if (!has_colors) {
        panic(1);
    }
    init_color(COLOR_BLACK, 0, 0, 0);
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    wattron(map, COLOR_PAIR(1));
    bkgd(COLOR_PAIR(1));
    srand(time(NULL));
    init_windows();
    init_hero();
    update_windows();
    return;
}

void quit() { //attempt to close the program gracefully at the user's request
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
