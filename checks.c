#include <curses.h>
#include <stdlib.h>
#include "globals.h"

void checks(bool moved) {
    if (hero.hp > hero.max_hp) hero.hp = hero.max_hp;
    idlok(output, TRUE);
    scrollok(output, TRUE);
    if (valid && moved) {
        turns++;
        valid = false;
    }
    return;
}

void impossible(int error) { //function for handling impossible events, but permit the game to continue. to interrupt the game, call panic() instead
    if (error == 0) {
        wprintw(output, "\nThere was an error with the far look command.");
    }
    else if (error == 1) {
        wprintw(output, "\nThere was an error with the look command.");
    }
    else if (error == 2) {
        wprintw(output, "\nUndefined object here. This is a bug.");
    }
    wprintw(output, " Maybe you should save or quit?");
    return;
}

void panic(int error) { //attempt to close the program gracefully after an unrecoverable error. note that the graceful stuff is not present yet
    endwin();
    if (error == 1) {printf("This terminal does not have full color support, or initializing colors has failed.\n");}
    else if (error == 2) {printf("Unable to properly initialize screen. You may have low system memory.\n");}
    else if (error == 3) {printf("Unable to properly update screen. You may have low system memory.\n");}
    else if (error == 4) {printf("Unable to properly implement screen. You likely have low system memory.\n");}
    else if (error == 5) {
        printf("Unable to exit curses mode. Please restart your terminal.\n");
        printw("Unable to exit curses mode. Please restart your terminal.\n");
    }
    else if (error == 6) {printf("Unable to scroll output window. You likely have low system memory.\n");}
    else if (error == 7) {printf("Unable to configure game output properly. You may have low system memory.\n");}
    else if (error == 8) {printf("This terminal is not equipped for proper game output. Please try a different terminal.\n");}
    else if (error == 9) {printf("Level generation called on level that already exists. This is a bug.\n");}
    else if (error == 10) {printw("Unable to properly clear screen. You may have low system memory.\n");}
    else if (error == 11) {printf("Map generation attempted on non-existent portion of the termainl screen. This is a bug.\n");}
    else {printf("An unspecified unrecoverable error has occurred.\nAn attempt was made to save your game.\nYou may want to reboot your computer before proceeding.");}
    exit(EXIT_FAILURE);
    return; //this should never be called
}
