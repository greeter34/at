#include <curses.h>
#include <stdlib.h>
#include <time.h>
#include "globals.h"

void init_windows() { //create windows for the map, hero stats, and output messages
    if ((output = initscr()) == NULL) panic(2);
    if ((map = initscr()) == NULL) panic(2);
    if ((stats = initscr()) == NULL) panic(2);
    output = newwin(6, (COLS - 1), 1, 1);
    map = newwin((LINES - 13), (COLS - 1), 7, 1);
    stats = newwin(4, (COLS - 1), (LINES - 6), 1);
    box(output, 0, 0);
    box(map, 0, 0);
    box(stats, 0, 0);
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
    else {printf("An unspecified unrecoverable error has occurred.\nAn attempt was made to save your game.\nYou may want to reboot your computer before proceeding.");}
    exit(EXIT_FAILURE);
    return; //this should never be called
}

void quit() { //attempt to close the program gracefully at the user's request
    mvwprintw(output, 1, 1, "Thank you for playing. Press any key to quit...");
    wrefresh(output);
    getch();
    endwin();
    exit(EXIT_SUCCESS);
    return; //this should never be called
}

void update_windows() {
    wnoutrefresh(stdscr);
    wnoutrefresh(curscr);
    wnoutrefresh(stats);
    wnoutrefresh(map);
    wnoutrefresh(output);
    doupdate();
    return;
}
