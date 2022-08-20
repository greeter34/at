#include <curses.h>
#include "globals.h"

void blank() { //blanks current hero position to prepare for moving him
    wmove(map, hero.y, hero.x); //move the cursor to be on the player
    wattroff(map, A_REVERSE);
    wprintw(map, " ");
    wmove(map, hero.y, hero.x);
    wattron(map, A_REVERSE);
    return;
}    

void move_hero(dir a) {
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
    checks();
    blank();
    return;
}

void loop() {
    update_windows(); //populate any relevant updates to the screen
    char todo = '0';
    todo = getch();
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
    
    wmove(map, hero.y, hero.x);
    wprintw(map, "@");
    mvwprintw(stats, 1, 1, "Turns: %d", turns);
    mvwprintw(stats, 2, 1, "HP: %d / %d ", hero.hp, hero.max_hp);
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
