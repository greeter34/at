#ifndef _GLOBALS
#define _GLOBALS

//global variables
extern long unsigned int turns;
extern WINDOW *stats, *map, *output, *stats_border, *map_border, *output_border;

long unsigned int turns;
WINDOW *stats, *map, *output, *stats_border, *map_border, *output_border;

typedef struct Monster {
    short unsigned int x;
    short unsigned int y;
    short unsigned int z;
    signed int hp;
    signed int max_hp;
    char name[10];
    long unsigned int gold;
} monster;

typedef enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    UPRIGHT,
    UPLEFT,
    DOWNRIGHT,
    DOWNLEFT
} dir;

monster hero;

//function definitions

//main.c
int main();
void loop();
void look();
void blank();
void move_hero(dir a);
void move_cursor(dir a);

//init.c
void init_game();
void init_hero();
void init_windows();
void panic();
void quit();
void update_windows();

//checks.c
void checks();

#endif
