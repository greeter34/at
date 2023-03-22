#include <curses.h>
#include <stdlib.h>
#include <string.h>
#include "globals.h"  

int roll(int dice, int max) {
    int to_return = 0, i = 0;
    for (i = 0; i < dice; i++) {
        to_return = to_return + ((rand() % max) + 1);
    }
    return to_return;
}

char *textual_month (int month) {
    char *month_name = malloc(sizeof(char) * 10);
    switch (g_time.month) {
        case 0:
            strcpy(month_name, "Spring\0");
            break;
        case 1:
            strcpy(month_name, "Summer\0");
            break;
        case 2:
            strcpy(month_name, "Autumn\0");
            break;
        case 3:
            strcpy(month_name, "Winter\0");
            break;
        default:
            impossible(4);
            strcpy(month_name, "Unknown\0");
            break;
    }
    return month_name;
}

char *fix_small_numbers(int smallnum) {
    char *to_return = malloc(sizeof(char) * 3);
    if (smallnum < 10) {
        sprintf(to_return, "0%d", smallnum);
    }
    else {
        sprintf(to_return, "%d", smallnum);
    }
    strcat(to_return, "\0");
    return to_return;
}

void loop() {
    char todo = '0';
    bool moved = false;
    redraw_screen();
    //update_windows(); //populate any relevant updates to the screen
    todo = wgetch(map);
    //movement commands
    if (todo == 'k') { //move up
        moved = move_hero(UP);
        valid = true;
    }
    if (todo == 'j') { //move down
        moved = move_hero(DOWN);
        valid = true;
    }
    if (todo == 'h') { //move left
        moved = move_hero(LEFT);
        valid = true;
    }
    if (todo == 'l') { //move right
        moved = move_hero(RIGHT);
        valid = true;
    }
    if (todo == 'n') { //move down and right
        moved = move_hero(DOWNRIGHT);
        valid = true;
    }
    if (todo == 'u') { //move up and right
        moved = move_hero(UPRIGHT);
        valid = true;
    }
    if (todo == 'y') { //move up and left
        moved = move_hero(UPLEFT);
        valid = true;
    }
    if (todo == 'b') { //move down and left
        moved = move_hero(DOWNLEFT);
        valid = true;
    }
    update_windows(); //we can never do this enough with curses apparently
    //non-movement commands
    /*if (todo == ';') { //far look
        look();
    }*/
    if (todo == ':') { //near look
        what_is_here();
    }
    if (todo == ',') { //take
        take();
    }
    if (todo == 'i') { //display inventory
        print_inventory();
    }
    checks(moved);
    mvwprintw(stats, 0, 1, "Stamina:\t%d", hero.stamina);
    mvwprintw(stats, 1, 1, "%s %d, %d - %d:%s:%s\t", textual_month(g_time.month), g_time.day, g_time.year, g_time.hour, fix_small_numbers(g_time.minute), fix_small_numbers(g_time.second));
    //mvwprintw(stats, 1, 1, "HP: %d / %d\tGold: BUG", hero.hp, hero.max_hp);
    wrefresh(stats);
    //non-movement commands
    if (todo == 'q') { //quit
        quit();
    }
    loop();
    return; //this should never be called
}

int main() {
    init_game();
    loop();
    return 0;
}
