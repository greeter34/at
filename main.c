#include <curses.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "globals.h"

void panic() { //this function is called for more severe problems, like if we have a call to malloc() fail
	endwin();
	srand(time(0));	
	int i = 0;
	char list[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char filename[21];
	for (i = 0; i < 15; i++) {
		filename[i] = list[rand() % 52]; 
	}
	filename[i] = '\0';	
	save(filename);	
	printf("Error: This program has experienced an unrecoverable error and must close now.\n");
	printf("An attempt to save your game was made. There is no guarantee that this attempt\n");
	printf("succeeded. We recommend checking for a save file and restarting your machine\n");
	printf("before running your game again. Thank you.\n");
	printf("Save attempted to this file:\n%s\n", filename);
	exit(EXIT_FAILURE);
}

void print_exits() {
	printw("Valid exits: ");	
	if (player.location->north) {printw("north ");}
	if (player.location->south) {printw("south ");}
	if (player.location->east) {printw("east ");}
	if (player.location->west) {printw("west ");}
	if (player.location->northeast) {printw("northeast ");}
	if (player.location->southeast) {printw("southeast ");}
	if (player.location->southwest) {printw("southwest ");}
	if (player.location->northwest) {printw("northwest ");}
	if (player.location->up) {printw("up ");}
	if (player.location->down) {printw("down ");}
	printw("\n\n");
	return;
}

void print_objects(object *where) { //displays a list of objects for a given location, or in inventory if *where points to player
	object *obj;
	bool obj_flag = false, inventory = false, print = true; /* is an object here? if not, no output
	// also are we checking inventory or a given location? also do we print the objects are here message? */
	if (obj->location == &player) inventory == true;
	for (obj = objs; obj < objs + TTL_OBJS; obj++) {
		if (obj->location == where && !obj->hidden && obj->weight != 0) {
			if (!obj_flag && !inventory && print) {
				printw("Objects that are here:\n\n");
				obj_flag = true;
			}
			if ((obj->location == &player) && !inventory && print) {
				printw("Objects in your inventory:\n\n");
				inventory = true;
				print = false;	
			}	
			printw("%s\n", obj->name);
		}
	}
	if (obj_flag || inventory) {
		printw("\n"); //print a new line to maintain consistent output with the display() function in the event that objects are present
		}
	if ((where == &player) && !inventory) {printw("No objects are in your inventory currently\n");}
	return;
}

void display(char *to_output) { //displays the argument passed to it to the user, in a way that prevents words from being split across lines whenever possible 
	int max_x = 0, max_y = 0, length = 0; //get maximum width and screen at time the function is called
	char description[MAX_DESC], *to_print, *token ; //copy the appropriate description, to_print will be written out to the screen while token is for strtok();
	getmaxyx(stdscr, max_y, max_x);	
	to_print = malloc(max_x + 1); //dynamically allocate enough memory for to_print to print one line
	if (to_print == NULL) panic();
	strcpy(to_print, "");
	strcpy(description, to_output);
	token = strtok(description, " ");
	while (token != NULL) {
		if (length + (strlen(token) + 2) > max_x) { 
		//if the current length of text plus the next token and one space exceeds the width of the screen, immediately print the line to screen 
			printw("%s\n", to_print);
			length = strlen(token);
			strcpy(to_print, "");
		}
		strcat(to_print, token);
		strcat(to_print, " ");
		length += (strlen(token) + 1); //we add one to account for the space	
		token = strtok(NULL, " ");
	}
	printw("%s\n\n", to_print);
	refresh();
	free(to_print);
	return;
}

void loop() {
	char output_text[MAX_DESC];
    if (player.location->been_here) {strcpy(output_text, player.location->short_desc);}
    else {
        strcpy(output_text, player.location->long_desc);
        player.location->been_here = true;
    }
    display(output_text);
	print_objects(player.location);
	print_exits();
	char cmd[80];
	getnstr(cmd, 80);
	parse(stl(cmd));
	if (running) {loop();}
}

int main() {
	initscr();
	keypad(stdscr, TRUE);
	cbreak();
	scrollok(stdscr, TRUE);
	start_color();
	init_color(COLOR_BLACK, 0, 0, 0); //sets black to darkest possible value. found on my terminal personally to be needed
	init_pair(1, COLOR_WHITE, COLOR_BLACK); 
	attron(COLOR_PAIR(1));
	bkgd(COLOR_PAIR(1));
	printw("Welcome to the adventure. Please enter your name below. Maximum 10 characters.\n");
	refresh();
	getnstr(player.name, 10);
	if (strlen(player.name) == 0) printw("Name not entered. Naming you Bob.\n");
	printw("Initializing game %s. Please wait...\n", player.name);
	refresh();
	init_game();
	printw("\nGame initialized. Press any key to begin...");
	refresh();
	getch();
	clear();
	loop();
	endwin(); //we eventually want execution to return to this point 
	printf("Program terminated.\n");	
	return 0;
}
