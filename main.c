#include <curses.h>
#include "globals.h"

void blank() { //blanks current hero position to prepare for moving him
    wmove(map, hero.y, hero.x); //move the cursor to be on the player
    wattroff(map, A_REVERSE);
    wprintw(map, ".");
    wmove(map, hero.y, hero.x);
    wattron(map, A_REVERSE);
    update_windows();
    return;
}    

bool move_hero(dir a) {
    int x = 0, y = 0;
    getyx(map, y, x); //store current coordinates of the hero in case the hero cannot move to the desired square
    char onscreen = '0';
    if (a == UP) {
        hero.y--;
    }
    if (a == DOWN) {
        hero.y++;
    }
    if (a == LEFT) {
        hero.x--;
    }
    if (a == RIGHT) {
        hero.x++;
    }
    if (a == DOWNRIGHT) {
        hero.x++;
        hero.y++;
    }
    if (a == UPRIGHT) {
        hero.x++;
        hero.y--;
    }
    if (a == UPLEFT) {
        hero.x--;
        hero.y--;
    }
    if (a == DOWNLEFT) {
        hero.x--;
        hero.y++;
    }
    wmove(map, hero.y, hero.x);
    onscreen = winch(map);
    if (onscreen == ' ') {
        hero.y = y;
        hero.x = x;
        wprintw(output, "\nOuch. You bump into solid rock.");
        return false;
    }
    return true;
}

void move_cursor(dir a) {
    int x = 0, y = 0;
    getyx(map, y, x);
    switch(a) {
        case UP:
            wmove(map, --hero.y, hero.x);
            break;
        case DOWN:
            wmove(map, ++hero.y, hero.x);
            break;
        case LEFT:
            wmove(map, hero.y, --hero.x);
            break;
        case RIGHT:
            wmove(map, hero.y, ++hero.x);
            break;
        case DOWNRIGHT:
            wmove(map, ++hero.y, ++hero.x);
            break;
        case UPRIGHT:
            wmove(map, --hero.y, ++hero.x);
            break;
        case UPLEFT:
            wmove(map, --hero.y, --hero.x);
            break;
        case DOWNLEFT:
            wmove(map, ++hero.y, --hero.x);
            break;
    }
    update_windows();
    return;
}

void look() {
    char todo = 0, x = hero.x, y = hero.y, here = 0;
    wprintw(map, "@"); //for some reason the hero always disappears here if we don't reprint the hero
    wmove(map, hero.y, hero.x); //put the cursor back to where the hero should be
    curs_set(1);
    while ((todo = wgetch(map)) != 'q') {
        if (todo == 'k') { //move up
            move_cursor(UP);
        }
        if (todo == 'j') { //move down
            move_cursor(DOWN);
        }
        if (todo == 'h') { //move left
            move_cursor(LEFT);
        }
        if (todo == 'l') { //move right
            move_cursor(RIGHT);
        }
        if (todo == 'n') { //move down and right
            move_cursor(DOWNRIGHT);
        }
        if (todo == 'u') { //move up and right
            move_cursor(UPRIGHT);
        }
        if (todo == 'y') { //move up and left
            move_cursor(UPLEFT);
        }
        if (todo == 'b') { //move down and left
            move_cursor(DOWNLEFT);
        }
        if (todo == '.') {
            what_is_here(winch(map));
        }
        update_windows();
    }
    curs_set(0);
    hero.x = x;
    hero.y = y;
    return;
}

void loop() {
    update_windows(); //populate any relevant updates to the screen
    char todo = '0';
    bool moved = false;
    todo = wgetch(map);
    blank();
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
    
    //non-movement commands
    if (todo == ';') {
            //wmove(map, hero.y, hero.x);
            look();
    }

    checks(moved);
    mvwprintw(stats, 1, 1, "Turns: %d", turns);
    mvwprintw(stats, 2, 1, "HP: %d / %d ", hero.hp, hero.max_hp);
    //non-movement commands
    if (todo == 'q') { //quit
        quit();
    }
    mvwprintw(map, hero.y, hero.x, "@");
    loop();
    return; //this should never be called
}

int main() {
    init_game();
    loop();
    return 0;
}
