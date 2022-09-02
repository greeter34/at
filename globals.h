#ifndef _GLOBALS
#define _GLOBALS

#define FLOORS 50
#define MAP_MAX_X 25
#define MAP_MAX_Y 80

//global variables
extern long unsigned int turns;
extern WINDOW *stats, *map, *output, *stats_border, *map_border, *output_border;
extern bool valid; //is an action that advances the number of turns valid?
extern char maps[FLOORS][MAP_MAX_X][MAP_MAX_Y];

long unsigned int turns;
WINDOW *stats, *map, *output, *stats_border, *map_border, *output_border;
bool valid;
char maps[FLOORS][MAP_MAX_X][MAP_MAX_Y];

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
bool move_hero(dir a);
void move_cursor(dir a);
int roll(int dice, int max);

//init.c
void init_game();
void init_hero();
void init_windows();
void quit();
void update_windows();
void generate_level();

//checks.c
void checks(bool moved);
void what_is_here(char a);
void impossible(int error);
void panic(int error);

//map.c
void draw_map(int level);

#endif
