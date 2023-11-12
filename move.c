#include "globals.h"

extern monster hero;

bool move_hero(dir a) {
    int x = 0, y = 0;
    bool moved = true;
    getyx(map, y, x); //store current coordinates of the hero in case the hero cannot move to the desired square
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
    switch(levels[hero.z][hero.x][hero.y].type) {
        case 6:
        case 7:
        case 10:
        case 11:
        case 12:
        case 13:
            wprintw(output, "\nOuch! You bump into a wall.");
            hero.y = y;
            hero.x = --x;
            moved = false;
            break;
    }
    return moved;
}

void move_cursor(dir a) {
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
