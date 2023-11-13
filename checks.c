#include <curses.h>
#include <stdlib.h>
#include "globals.h"

extern monster hero;

void fix_time() {
    // Convert excess seconds to minutes
    g_time.minute += g_time.second / 60;
    g_time.second %= 60;

    // Convert excess minutes to hours
    g_time.hour += g_time.minute / 60;
    g_time.minute %= 60;

    // Convert excess hours to days
    g_time.day += g_time.hour / 24;
    g_time.hour %= 24;

    // Update weekday
    g_time.weekday = (g_time.weekday + g_time.day) % 7;

    // Convert excess days to months
    g_time.month += g_time.day / 30;
    g_time.day %= 30;

    // Adjust months to years (assuming 4 months per year as per original logic)
    g_time.year += g_time.month / 4;
    g_time.month %= 4;
}

void checks(bool moved) {
    if (hero.stamina > hero.max_stamina) hero.stamina = hero.max_stamina;
    idlok(output, TRUE);
    scrollok(output, TRUE);
    if (valid && moved) {
        turns++;
        g_time.second += 1; //it takes 1 second to move somewhere else nearby
        fix_time();
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
    else if (error == 3) {
        wprintw(output, "\nHero in solid rock?");
    }
    else if (error == 4) {
        wprintw(output, "\nMonth is invalid. Showing it as %d", g_time.month);
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
