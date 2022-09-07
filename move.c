#include "globals.h"

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
        hero.x = --x; //not sure why we need to reduce x by one here. if someone can explain this to me please do so
        wprintw(output, "\nOuch. You bump into solid rock.");
        return false;
    }
    if ((maps[hero.z][hero.x][hero.y] == '1') || (maps[hero.z][hero.x][hero.y] == '2') || (maps[hero.z][hero.x][hero.y] == '3') || (maps[hero.z][hero.x][hero.y] == '4') || (maps[hero.z][hero.x][hero.y] == '5') || (maps[hero.z][hero.x][hero.y] == '6')) {
        hero.y = y;
        hero.x = --x;
        wprintw(output, "\nOuch. You bump into a wall.");
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
    return;
}
