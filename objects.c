#include <stdlib.h>
#include <string.h>
#include "globals.h"

void create_object(int z, int x, int y, char glyph) {
    ttl_objects++;
    objects = realloc(objects, (sizeof(object) * ttl_objects));
    ttl_objects--;
    //the following 5 variables should not depend on anything external
    objects[ttl_objects].z = z;
    objects[ttl_objects].x = x;
    objects[ttl_objects].y = y;
    objects[ttl_objects].glyph = glyph;
    objects[ttl_objects].exists = TRUE;
    //the following we set to the most common values. they can then be adjusted later if needed
    objects[ttl_objects].visible = TRUE; //most objects will be visible
    objects[ttl_objects].infravisible = FALSE; //most objects will not have a heat signature
    objects[ttl_objects].moveable = TRUE; //we can pick up most objects
    objects[ttl_objects].edible = FALSE; //only food is edible
    objects[ttl_objects].amount = 1; //only one copy of most objects per space
    //now things might change depending on what the object is
    if (glyph == '$') {
        strcpy(objects[ttl_objects].name, "gold");
        objects[ttl_objects].amount = (roll(5, 10) + (hero.level * hero.level)); //heros find more money the more experienced they are
    }
    if (glyph == '}') {
        strcpy(objects[ttl_objects].name, "fountain");
        objects[ttl_objects].moveable = FALSE;
    }
    ttl_objects++;
    return;
}
