#include <curses.h>
#include "globals.h"

void blank() { //blanks current hero position to prepare for moving him
    wmove(map, hero.y, hero.x); //move the cursor to be on the player
    wattroff(map, A_REVERSE);
    wprintw(map, " ");
    wmove(map, hero.y, hero.x);
    wattron(map, A_REVERSE);
    update_windows();
    return;
}    

void move_hero(dir a) {
    int x = 0, y = 0;
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
    blank();
    return;
}

//the following two functions do not work properly yet and likely require extensive modifcations
void move_cursor(dir a) {
    int x = 20, y = 20;
    getyx(map, y, x);
    switch(a) {
        case UP:
            wmove(map, hero.y--, hero.x);
            break;
        case DOWN:
            wmove(map, hero.y++, hero.x);
            break;
        case LEFT:
            wmove(map, hero.y, hero.x--);
            break;
        case RIGHT:
            wmove(map, hero.y, hero.x++);
            break;
        case DOWNRIGHT:
            wmove(map, hero.y++, hero.x++);
            break;
        case UPRIGHT:
            wmove(map, hero.y--, hero.x++);
            break;
        case UPLEFT:
            wmove(map, hero.y--, hero.x--);
            break;
        case DOWNLEFT:
            wmove(map, hero.y++, hero.x--);
            break;
    }
    update_windows();
    return;
}

void look() { //this code needs work
    char todo = 0, x = hero.x, y = hero.y;
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
    todo = wgetch(map);
    blank();
    //movement commands
    if (todo == 'k') { //move up
        move_hero(UP);
    }
    if (todo == 'j') { //move down
        move_hero(DOWN);
    }
    if (todo == 'h') { //move left
        move_hero(LEFT);
    }
    if (todo == 'l') { //move right
        move_hero(RIGHT);
    }
    if (todo == 'n') { //move down and right
        move_hero(DOWNRIGHT);
    }
    if (todo == 'u') { //move up and right
        move_hero(UPRIGHT);
    }
    if (todo == 'y') { //move up and left
        move_hero(UPLEFT);
    }
    if (todo == 'b') { //move down and left
        move_hero(DOWNLEFT);
    }
    
    //non-movement commands
    if (todo == ';') {
            wmove(map, hero.y, (hero.x - 1));
            look();
    }

    checks();
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
