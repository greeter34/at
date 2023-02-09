#include <curses.h>
#include "globals.h"
/*
void what_is_there(char a) { //this function is bugged. first wprintw call fails if hero has not moved this game session
    wprintw(output, "\n'%c' - ", a);
    switch(a) {
        case '.':
            wprintw(output, "Floor of room");
            break;
        case '@':
            wprintw(output, "A human, elf, or heroic character");
            break;
        case ' ':
            wprintw(output, "Solid rock");
            break;
        case '%':
            wprintw(output, "Food");
            break;
        case '$':
            wprintw(output, "Gold");
            break;
        case '}':
            wprintw(output, "A fountain");
            break;
        case '#':
            wprintw(output, "A sink or a hallway");
            break;
        default:
            wprintw(output, "Undefined.", a);
            update_windows();
            impossible(0);
            break;
    }
    update_windows();
    return;
}

void what_is_here() {
    int i = 0;
    bool objects_here = FALSE;
    wprintw(output, "\n");
    for (i = 0; i < ttl_objects; i++) {
        if ((objects[i].z == hero.z) && (objects[i].x == hero.x) && (objects[i].y == hero.y)) {
            objects_here = TRUE;
            if (objects[i].glyph == '$') {
                wprintw(output, "You see %d %s here", objects[i].amount, objects[i].name);
                update_windows();
            }
            else if (objects[i].glyph == '}') {
                wprintw(output, "You see a %s here", objects[i].name);
                update_windows();
            }
            else {
                wprintw(output, "Undefined object.\n");
                update_windows();
                impossible(2);
            }
        }
    }
    if (!objects_here) {
        if (maps[hero.z][hero.x][hero.y] == '.') {
            wprintw(output, "You see nothing here.");
        }
        else if (maps[hero.z][hero.x][hero.y] == '#') {
            wprintw(output, "You see a sink or a hallway here.");
        }
        else {
            wprintw(output, "Unknown object here.");
            impossible(1);
        }
    }
    return;
}

void look() {
    char todo = 0, x = hero.x, y = hero.y, here = 0;
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
        here = winch(map);
        if (todo == '.') {
            what_is_there(here);
        }
    }
    curs_set(0);
    hero.x = x;
    hero.y = y;
    return;
}
*/
