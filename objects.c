#include <curses.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "globals.h"

void create_object(int z, int x, int y, char glyph) {
    /* We first increment total objects, so that we reallocate the correct amount of *
     * new space for the object. We decrease immediately afterwards to maniuplate    *
     * that object and set variables. We increase again at the very end to have the  *
     * total number of objects again */
    ttl_objects++;
    objects = realloc(objects, (sizeof(object) * ttl_objects));
    ttl_objects--;
    //the following 7 variables should not depend on anything external
    objects[ttl_objects].z = z;
    objects[ttl_objects].x = x;
    objects[ttl_objects].y = y;
    objects[ttl_objects].glyph = glyph;
    objects[ttl_objects].exists = 1; //most objects exist
    objects[ttl_objects].id = ttl_objects; //this may be removed later
    objects[ttl_objects].owner = -1; //-1 is no owner as the ID attribute is unsigned so always positive or 0. this should be for objects on the ground only
    //the following we set to the most common values. they can then be adjusted later if needed
    objects[ttl_objects].visible = 1; //most objects will be visible but not have a heat signature
    objects[ttl_objects].moveable = 1; //we can pick up most objects
    objects[ttl_objects].edible = 0; //only food is edible
    objects[ttl_objects].amount = 1; //only one copy of most objects per space
    objects[ttl_objects].buc = 1; //most objects are uncursed
    //now things might change depending on what the object is
    if (glyph == '$') {
        strcpy(objects[ttl_objects].name, "gold");
        objects[ttl_objects].amount = (roll(5, 10) + (hero.exp * hero.exp)); //heros find more money the more experienced they are. will need function to calculate hero's level or this gets unbalanced
    }
    if (glyph == '}') {
        strcpy(objects[ttl_objects].name, "fountain");
        //objects[ttl_objects].moveable = FALSE; //commented out for debugging purposes
    }
    ttl_objects++;
    return;
}

void destroy_object(int a) {
    objects[a].z = 101; //this puts it out of bounds on level 101
    objects[a].exists = 0; //this prevents interaction by functions which check this
    objects[a].glyph = '9'; //this assigns an invalid glyph to the object
    return;
}

void print_inventory() {
    int i = 0, line = 1;
    bool has_objects = FALSE;
    //following code is broken. do not use
    /*
    char prefix[10];
    for(i = 0; i < 52; i++) {
        if (items[i].amount > 0) {
            if (items[i].amount == 1) {
                strcpy(prefix, "a(n)");
                wprintw(output, "\n%s %s (item %d in inventory)", prefix, items[i].name, i);
            }
            else {
                //strcpy(prefix, (char *) items[i].amount);
                sprintf(prefix, "%d", items[i].amount);
                wprintw(output, "\n%s $ss", prefix, items[i].name);                
            }
            wrefresh(output);
            has_objects = true;
        }
    }
    if (!has_objects) {
        wprintw(output, "\nYou have no inventory!");
        wrefresh(output);
    }
    */
    for(i = 0; i < ttl_objects; i++) {
        if (objects[i].owner == 0) {
            has_objects = true;
            break;
        }
    }
    if (has_objects) {
        WINDOW *inventory = newwin(28, 52, 4, 30);
        box(inventory, 0, 0);
        wmove(inventory, 1, 1);
        for (i = 0; i < ttl_objects; i++) {
            if (objects[i].owner == 0) {
                wprintw(inventory, "%s", objects[i].name);
                line++;
                wmove(inventory, line, 1);
                wrefresh(inventory);
            }
        }
        getch(); //so user has time to look at inventory. we don't care about this key press
    }
    if (!has_objects) {
        wprintw(output, "\nYour inventory is empty!");
        wrefresh(output);
    }
    return;
}

void take() {
    int i = 0;
    bool taken = false;
    for (i = 0; i < ttl_objects; i++) {
        if ((objects[i].z == hero.z) && (objects[i].x == hero.x) && (objects[i].y == hero.y) && (objects[i].moveable)) { //if object location = hero location & if object is moveable
            if (objects[i].glyph == '$') {
                wprintw(output, "\nYou add %d gold to your wallet.", objects[i].amount);
                wrefresh(output);
                taken = true;
                destroy_object(i); //gold should always be destroyed on pickup. new gold object can be created later if needed
            }
            if (objects[i].glyph == '}') {
                wprintw(output, "\nYou somehow pick up the %s and take it with you.", objects[i].name);
                wrefresh(output);
                taken = true;
                objects[i].owner = 0;
            }
        }
    }
    if (!taken) {
        wprintw(output, "\nYou take nothing.");
        wrefresh(output);
    }
    return;
}
