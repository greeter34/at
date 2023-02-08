#ifndef GLOBALS
#define GLOBALS
#include <stdbool.h>
#define MAX_DESC 1024 
#define TTL_OBJS 5 
#define TTL_LOCATIONS 32 
//MAX_DESC will be the maximum length of a string for the long_desc in the locations structures
//TTL_OBJS is the total number of actual objects in the game that the player can interact with

//type definitions for structures go here. global variables go in globals.c

enum dir {NORTH, SOUTH, EAST, WEST, NORTHEAST, NORTHWEST, SOUTHEAST, SOUTHWEST, UP, DOWN};

typedef struct objects {
	char name[30];
	int weight; //set to 0 if item cannot be moved
	short unsigned int id;
	struct objects *location; //set location to NULL to destroy an object
	bool been_here;
	bool hidden; //objects can remain hidden until exmaine command is used to reveal them, at which point hidden is set to false
	char short_desc[80];
	char long_desc[MAX_DESC];
	//location pointers
	struct objects *north;
	struct objects *northeast;
	struct objects *east;
	struct objects *southeast;
	struct objects *south;
	struct objects *southwest;	
	struct objects *west;
	struct objects *northwest;
	struct objects *up;
	struct objects *down;
} object;
 
extern bool running;
extern object player;
extern object objs[TTL_OBJS];
extern object locations[TTL_LOCATIONS];

//function definitions

//parser.c 
void parse(char *cmd);
char *stl(char *string);

//main.c
void unknown_cmd();
void help();
int main();
void display();
void quit(int reason);
void init_game();
void loop();
void display(char *to_output);
void print_objects(object *where);
void print_exits();
void panic();

//cmds.c
void unknown_cmd();
void help();
void quit();
void move_object(int direction);
void take(char *noun);
void use(char *noun);
void drop(char *noun);
void examine(char *noun);
void count(char *noun);

//init.c
void init_game();

//files.c
void save();
char *prompt();
void load();

#endif
