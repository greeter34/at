#include <curses.h>

#ifndef _GLOBALS
#define _GLOBALS

#define FLOORS 100
#define MAP_MAX_X 25
#define MAP_MAX_Y 80

//global variables
extern long unsigned int turns, seed, ttl_objects;
extern WINDOW *stats, *map, *output, *stats_border, *map_border, *output_border;
extern bool valid; //is an action that advances the number of turns valid?
extern char maps[FLOORS][MAP_MAX_X][MAP_MAX_Y];
extern bool been_here[50];

long unsigned int turns, seed, ttl_objects;
WINDOW *stats, *map, *output, *stats_border, *map_border, *output_border;
bool valid;
char maps[FLOORS][MAP_MAX_X][MAP_MAX_Y];
bool been_here[50];

typedef struct Monster {
    short unsigned int x;
    short unsigned int y;
    short unsigned int z;
    signed int hp;
    signed int max_hp;
    char name[10];
    long unsigned int gold;
    short unsigned int level;
} monster;

typedef struct Object {
    char name[20];
    short unsigned int amount;
    short unsigned int x;
    short unsigned int y;
    short unsigned int z;
    char glyph;
    char buc;
    bool exists;
    bool moveable;
    bool visible;
    bool infravisible;
    bool edible;
} object;

extern object *objects;

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
object *objects;

//function definitions

//main.c
int main();
void loop();
int roll(int dice, int max);

//init.c
void init_game();
void init_hero();
void init_windows();
void quit();
void update_windows();

//checks.c
void checks(bool moved);
void impossible(int error);
void panic(int error);

//map.c
void draw_map(int level);
void draw_objects(int level);
void draw_monsters(int level);
void redraw_screen();
void generate_level();

//objects.c
void create_object(int x, int y, int z, char glyph);

//look.c
void what_is_there(char a);
void what_is_here();
void look();

//move.c
bool move_hero(dir a);
void move_cursor(dir a);

#endif
