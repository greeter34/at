#include <curses.h>
#include <stdlib.h>
#include <time.h>
#include "globals.h"

#define MAP_MAX_X 25
#define MAP_MAX_Y 80

void init_windows() { //create windows for the map, hero stats, and output messages
    int mapx = 0, mapy = 0; //used to store maximum width and height of map
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
    output = newwin(7, (COLS - 3), 2, 2);
    map = newwin((mapx - 2), (mapy - 2), 8, 2);
    stats = newwin(2, (COLS - 3), (LINES - 6), 2);
    box(output_border, 0, 0);
    box(map_border, 0, 0);
    box(stats_border, 0, 0);
    return;
}

void init_hero() { //initialize hero
    hero.gold = 0;
    hero.x = 10;
    hero.y = 10;
    wmove(map, hero.y, hero.x);
    wattron(map, A_REVERSE);
    wprintw(map, "@");
    return;
}

void init_game() { //initialize game variables
    turns = 0;
    initscr();
    cbreak();
    noecho();
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

void panic(int error) { //attempt to close the program gracefully after an unrecoverable error
    endwin();
    if (error == 1) {printf("This terminal does not have full color support, or initializing colors has failed.\n");}
    if (error == 2) {printf("Unable to properly initialize screen. You may have low system memory.\n");}
    if (error == 3) {printf("Unable to properly update screen. You may have low system memory.\n");}
    if (error == 4) {printf("Unable to properly implement screen. You likely have low system memory.\n");}
    if (error == 5) {
        printf("Unable to exit curses mode. Please restart your terminal.\n");
        printw("Unable to exit curses mode. Please restart your terminal.\n");
    }
    else {printf("An unspecified unrecoverable error has occurred.\nAn attempt was made to save your game.\nYou may want to reboot your computer before proceeding.");}
    exit(EXIT_FAILURE);
    return; //this should never be called
}

void quit() { //attempt to close the program gracefully at the user's request
    if (wprintw(output, "Thank you for playing. Press any key to quit...\n") == ERR) panic(4);
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
    if (wnoutrefresh(map) == ERR) panic(3);
    if (wnoutrefresh(output) == ERR) panic(3);
    if (!called) {
        if (wnoutrefresh(stats_border) == ERR) panic(4);
        if (wnoutrefresh(map_border) == ERR) panic(4);
        if (wnoutrefresh(output_border) == ERR) panic(4);
        called = TRUE;
    }
    if (doupdate() == ERR) panic(5);
    return;
}
