#include <curses.h>

#ifndef _GLOBALS
#define _GLOBALS

#define FLOORS 100
#define MAP_MAX_X 25
#define MAP_MAX_Y 80

//global variables
extern long unsigned int turns, seed, ttl_objects, ttl_monsters;
extern WINDOW *stats, *map, *output, *stats_border, *map_border, *output_border;
extern bool valid; //is an action that advances the number of turns valid?
//extern char maps[FLOORS][MAP_MAX_X][MAP_MAX_Y];
extern bool been_here[50];
extern char tile_types[10];

long unsigned int turns, seed, ttl_objects, ttl_monsters;
WINDOW *stats, *map, *output, *stats_border, *map_border, *output_border;
bool valid;
//char maps[FLOORS][MAP_MAX_X][MAP_MAX_Y];
bool been_here[50];
char tile_types[10];

//global structure definitions

typedef struct Monster {
    short unsigned int x : 6;
    short unsigned int y : 8;
    short unsigned int z : 8;
    long unsigned int id;
    unsigned int exp;
    signed int hp;
    unsigned int max_hp;
    char name[10];
    char called[50];
    int conf : 1;
    int stun : 1;
    int paralyzed : 1;
    int blind : 1;
    int deaf : 1;
    int hallucinating : 1;
} monster;

typedef struct Object {
    char name[20];
    char called[50];
    short unsigned int amount;
    short unsigned int x : 6;
    short unsigned int y : 8;
    short unsigned int z : 8;
    long unsigned int id;
    long signed int owner; //matches ID of monster that owns the item, if any. the hero is always 0
    char glyph;
    int buc : 2; //0 is cursed, 1 is uncursed, 2 is blessed. 3 is an impossible();
    int exists : 1;
    int moveable : 1;
    int visible : 2; //objects can be visible, invisible, or infravisible. infravisible implies visible. 0 is invisible. 1 is visible. 2 is infravisible. 3 is an impossible();
    int edible : 1;
} object;

typedef struct Tile {
    short unsigned int x : 6;
    short unsigned int y : 8;
    short unsigned int z : 8;
    unsigned int walkable : 1;
    unsigned int lit : 1;
    char glyph;
    int type;
    monster *m_here; //pointer to a monster that is here
} tile;

typedef struct Inventory {
    int amount;
    char name[50]; //name as it should appear in inventory. longer than item name as this can be shown as "uncursed thing" or similar
} inventory; //array of 52 items for maximum number of inventory slots

//global structures
extern object *objects;
extern tile levels[FLOORS][MAP_MAX_X][MAP_MAX_Y];
extern inventory items[52];

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

tile levels[FLOORS][MAP_MAX_X][MAP_MAX_Y];
monster hero;
object *objects;
inventory items[52];

//function definitions

//main.c
int main();
void loop();
int roll(int dice, int max);

//init.c
void init_game();
void initialize_color();
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
void generate_room(int segment);

//objects.c
void create_object(int x, int y, int z, char glyph);
void destroy_object(int a);
void print_inventory();
void take();

//look.c
void what_is_there(char a);
void what_is_here();
void look();

//move.c
bool move_hero(dir a);
void move_cursor(dir a);

//windows.c
void init_windows();
void update_windows();
void fix_windows();

#endif
