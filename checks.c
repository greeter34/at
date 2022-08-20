#include <curses.h>
#include "globals.h"

void checks() {
    if (hero.hp > hero.max_hp) hero.hp = hero.max_hp;
    idlok(output, TRUE);
    scrollok(output, TRUE);
    if ((turns % 10) == 5) { //this conditional is for testing only. will be removed later
        wprintw(output, "\nTurns played so far: %d", turns);
        }
    turns++;
    return;
}
