#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include <limits.h>
#include "globals.h"

/* This group of functions relates to file handling, specifically saving and loading *    
 * game files. These functions should now be complete, and should not need any       *
 * more expansion as the game develops. However they should now be complete. A       *
 * temporary basic object is created containing an object ID (identical to the       *
 * unique location ID where the object exists, set to USHRT_MAX if in player         *
 * inventory) along with the needed boolean values been_here and hidden. These are   * 
 * then written to files with fwrite() so that no pointers or memory addresses are   *
 * saved. We simply read back out into the same temporary basic object and           *
 * reinitialize any data necessary with the restore function. If you observe any     *
 * bugs in this code please reach out immediately via GitHub                         */ 

struct by_lightning { //temporary basic object, global to this file only (not used elsewhere)
	char name[10]; //player name is limited to 10 characters or fewer. no other names are copied
	short unsigned int id;
	bool been_here;
	bool hidden;
} temp_object;

char *prompt() { //call this to query the user for a save or load file location
	static char path[100];
	printw("Please enter a file name\nNote: Name can be relative or an absolute path\n");
	getnstr(path, 100);
	return path;
}

void restore(struct objects *temporary, int i) {
	if (temporary->id == USHRT_MAX) {temporary->location = &player;}
	else {temporary->location = &locations[i];}
	return;
}

void save(char *destination) {
	FILE *savefile = fopen(destination, "wb");
	int i = 0;
	bool failed = false; //assume success until confirmed otherwise
	if (savefile == NULL) {
		failed = true;	
		printw("Cannot open %s: File is NULL\nPlease specify another file path. This may be caused by a permissions issue.\nOtherwise, you may be out of disk space.\n\n");
	}
	if (!failed) {
		for (i = 0; i < TTL_OBJS; i++) { //save objects first
			temp_object.id = objs[i].id;
			temp_object.hidden = objs[i].hidden;
			fwrite(&temp_object, sizeof(temp_object), 1, savefile);
		}	
		for (i = 0; i < TTL_LOCATIONS; i++) { //save locations next
			temp_object.id = locations[i].id;
			temp_object.been_here = objs[i].been_here;
			fwrite(&temp_object, sizeof(temp_object), 1, savefile);
		}

		strcpy(temp_object.name, player.name);
		temp_object.id = player.location->id;
		fwrite(&temp_object, sizeof(temp_object), 1, savefile);
		//loop can go here for sprites when needed

		fclose(savefile);
	}	
	return;
}

void load(char *destination) { //this function is incomplete
	FILE *loadfile = fopen(destination, "rb");
	int i = 0;	
	bool failed = false; //assume success until confirmed otherwise
	if (loadfile == NULL) {
		failed = true;	
		printw("Could not open %s: File is NULL\n", destination);
		refresh();
   	}
	if (!failed) {
		for (i = 0; i < TTL_OBJS; i++) {
			fread(&temp_object, sizeof(temp_object), 1, loadfile);
			objs[i].id = temp_object.id;
			objs[i].hidden = temp_object.hidden;
			restore(objs, i);
		}
		for (i = 0; i < TTL_LOCATIONS; i++) {
			fread(&temp_object, sizeof(temp_object), 1, loadfile);
			locations[i].id = temp_object.id;
			locations[i].been_here = temp_object.been_here;
			//restore(locations, i);
		}

		fread(&temp_object, sizeof(temp_object), 1, loadfile);
		strcpy(player.name, temp_object.name);
		player.location->id = temp_object.id;
		player.location = &locations[player.location->id];	
		fclose(loadfile);	
	}
	return;
}
