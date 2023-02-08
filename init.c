#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include "globals.h"

//detailed comments explaining the comments in this file can be found in globals.c

void init_game() {
	//locations

	int i = 0;
	for (i = 0; i < TTL_LOCATIONS; i++) {
		//below, we'll set all location pointers NULL, then only set location pointers as necessary from there
		locations[i].north = NULL;
		locations[i].south = NULL;
		locations[i].east = NULL;
		locations[i].west = NULL;
		locations[i].northeast = NULL;
		locations[i].northwest = NULL;
		locations[i].southeast = NULL;
		locations[i].southwest = NULL;
		locations[i].up = NULL;
		locations[i].down = NULL;
		locations[i].id = i;
		locations[i].been_here = false; //we have not been anywhere in the game when this function is called 
		if (i < TTL_OBJS) {
			objs[i].hidden = false;
			objs[i].weight = 0;
		}	
	}
	
	//Living room, starting location for player 
	locations[0].north = &locations[1]; //ground floor hall 
	strcpy(locations[0].name, "Living room");
	strcpy(locations[0].short_desc, "The main living room of the mansion");
	strcpy(locations[0].long_desc, "You are in a large living room, approximately four meters by five meters. "
		"Bay windows let in the sunlight from the east. A cast iron fireplace on the west end of the room is "
		"visible. You can make out engravings on the very back that depict pioneer life in days gone by. A "
		"couple of black chandeliers with light bulbs in the shape of candle flames can provide additional light by night.");
	player.location = &locations[0];
	
	//Ground floor hall 
	locations[1].south = &locations[0]; //living room
	locations[1].east = &locations[2]; //vestibule
	locations[1].west = &locations[3]; //back hall
	locations[1].northwest = &locations[4]; //dining room
	locations[1].up = &locations[12]; //west wing hall
	strcpy(locations[1].name, "Ground floor hall"); //this name needs to be better
	strcpy(locations[1].short_desc, "You find yourself in the hallway on the ground floor of the mansion.");
	strcpy(locations[1].long_desc, "You are in a grand hallway with an ornate wooden staircase that can take you "
		"elsehwere in the estate. A buffet table rests neatly against the wall and stained glass windows give "
		"the sunlight a more muted yet colorful effect in here. One singular bright light, surrounded in a globe "
		"like structure of uranium glass casts a greenish tint to everything here.");

	//Front vestibule 
	locations[2].west = &locations[1];
	strcpy(locations[2].name, "Front vestibule"); //ground floor hall
	strcpy(locations[2].short_desc, "The front door vestibule.");
	strcpy(locations[2].long_desc, "You are in the vestibule to the front door. An old gray mat covers the floor. "
		"Prismatic shards of glass held beautifully together in their frame shower the area in rainbow colored "
		"light. An old name plate on the door bears the name of your grandfather, the man who bought this house many years ago.");	

	//Back hall 
	locations[3].south = &locations[7]; //side door
	locations[3].east = &locations[1]; //ground floor hall
	locations[3].west = &locations[6]; //kitchen
	locations[3].up = &locations[11]; //east wing hall	
	strcpy(locations[3].name, "Back hall");
	strcpy(locations[3].short_desc, "The back hallway of the old mansion");
	strcpy(locations[3].long_desc, "You are in the back hallway of the mansion. A single ceiling light with three bulbs "
		"provides illumination. A gray plastic outdoor carpet protects the floor, a stark contrast to the original "
		"hardwood floors in most of the rest of the house. Various coats hang from several bars in the corner of the "
		"room as well.");	

	//Dining room 
	locations[4].southeast = &locations[1]; //ground floor hall
	locations[4].west = &locations[5]; //pantry
	strcpy(locations[4].name, "Dining room");
	strcpy(locations[4].short_desc, "You are in the main dining room");
	strcpy(locations[4].long_desc, "You find yourself in a huge octagonal dining room. Huge windows stretching nearly to "
		"the top of the 12 foot ceilings let copious amounts of bright light from the north. An antique dining room set "
		"complete with upholstered chairs is on the south end of the room. A singular large black light fixture with three "
		"bulbs can provide additional lighting at night. A large beveled mirror hanging above the dining room set makes the "
		"room look even larger. There is also a couch along the north wall by the windows.");		

	//Pantry 
	locations[5].east = &locations[4]; //dining room
	locations[5].south = &locations[6]; //kitchen
	strcpy(locations[5].name, "Pantry");
	strcpy(locations[5].short_desc, "A pantry, full of dishware, complete with a sink for cleaning the dishes.");
	strcpy(locations[5].long_desc, "This is the pantry. It is full of various crystal dishware and even has a kitchen sink with "
		"separate hot and cold water taps. A false ceiling is here in a brick like pattern. Brown and white tile flooring "
		"here reminds you of what this small town is most famous for, cattle.");
	
	// Kitchen
	locations[6].north = &locations[5]; //pantry
	locations[6].east = &locations[3]; //back hall
	locations[6].northwest = &locations[8]; //back vestibule
	locations[6].northeast = &locations[10]; //food closet	
	strcpy(locations[6].name, "Kitchen");
	strcpy(locations[6].short_desc, "The kitchen, complete with many amenities but oddly devoid of cupboards.");
	strcpy(locations[6].long_desc, "The kitchen of the estate. A few small counters dot the otherwise large kitchen. One huge "
		"fluorescent light provides all the lighting this room ever needs. A gas stove sits along the south wall, able to "
		"provide a hot meal even without power. This kitchen is oddly devoid of any cupboards.");

	//Side door
	locations[7].north = &locations[3]; //back hall
	locations[7].down = &locations[27]; //Basement stairs landing
	strcpy(locations[7].name, "Side door");
	strcpy(locations[7].short_desc, "You arrive at the side door, and are standing on an ornate iron grate.");
	strcpy(locations[7].long_desc, "You're at the side door of the house. An iron grate with an intricate pattern is below your "
		"feet. You can see the estate next door through the south facing window. It isn't nearly as big as the one you're "
		"in right now however. The lighting mixed with the purple walls gives an odd sense of dreariness that you don't "
		"experience anywhere else in this mansion.");

	//Back vestibule
	locations[8].south = &locations[6]; //kitchen
	locations[8].north = &locations[9]; //ground floor restroom	
	locations[8].west = &locations[31]; //garage	
	strcpy(locations[8].name, "Back vestibule");
	strcpy(locations[8].short_desc, "The back vestibule, leading to the garage, kitchen, or ground floor restroom");
	strcpy(locations[8].long_desc, "The back vestibule has smaller floor tiles here, as well as a washing machine. There is also a "
		"laundry chute that comes down from one of the second floor bedrooms. Plastic panels diffuse the overhead fluorescent "
		"light and turn it into a gentler glow.");

	//Ground floor restroom
	locations[9].south = &locations[8]; //back vestibule
	strcpy(locations[9].name, "Ground floor restroom");
	strcpy(locations[9].short_desc, "The ground floor restroom, with an odd greenish pattern on the walls.");
	strcpy(locations[9].long_desc, "You find yourself in the ground floor restroom. An antique claw foot tub is here, along with "
		"a very old sink. The faucets are fused in place and no longer open. The same plastic paneling in the vestibule "
		"also adorns the ceiling here. A tiny window by the ceiling, too high up to see through, also lets in the gentle "
		"light of the afternoon sun.");

	//Food closet
	locations[10].southwest = &locations[6]; //kitchen
	strcpy(locations[10].name, "Food closet");
	strcpy(locations[10].short_desc, "You are in the rather dark food closet.");
	strcpy(locations[10].long_desc, "This old food closet has barely enough room for you to stand in it. You remember as a "
		"child being able to climb the shelves from the ground all the way to the top. All sorts of cans and boxes of "
		"food line the shelves here. There's enough food to ensure that you won't go hungry for several months.");

	//West wing hall
	locations[11].east = &locations[12]; //east wing hall	
	locations[11].north = &locations[23]; //second floor restroom
	locations[11].west = &locations[20]; //twin bedroom
	locations[11].northwest = &locations[22]; //spare bedroom
	locations[11].down = &locations[3]; //back hall
	locations[11].up = &locations[24]; //main attic entryway
	strcpy(locations[11].name, "West wing hall");
	strcpy(locations[11].short_desc, "You are in the western half of the second floor.");
	strcpy(locations[11].long_desc, "The western half of the second floor has one lonely ceiling fixture with three light "
		"bulbs. A wall sconce also hangs by the staircase. You used to twist the wall sconce to the left as a child "
		"to pretend that it would unlock secret passageways elsewhere on the estate. Hardwood floors appear througout "
		"the halls. Two of the estate's six bedrooms are located here.");

	//East wing hall
	locations[12].west = &locations[11]; //west wing hall
	locations[12].down = &locations[1]; //ground floor hall
	locations[12].northwest = &locations[13]; //master bedroom
	locations[12].east = &locations[14]; //pink bedroom
	locations[12].southeast = &locations[16]; //front bedroom
	locations[12].south = &locations[18]; //side bedroom	
	strcpy(locations[12].name, "East wing hall");
	strcpy(locations[12].short_desc, "You are in the eastern half of the second floor.");
	strcpy(locations[12].long_desc, "The western half of the second floor has far more indoor lighting than the eastern "
		"half, with a wall sconce and a ceiling fan that houses several light bulbs. Stained glass windows on the "
		"down staircase also let in copious amounts of light. A balcony type area overlooks the ground floor hallway "
		"and triggers your fear of heights ever so slightly. Four of the estate's six bedrooms are located here.");

	//Master bedroom	
	locations[13].southeast = &locations[12]; //east wing hall
	strcpy(locations[13].name, "Master bedroom");
	strcpy(locations[13].short_desc, "You are in the master bedroom, spacious and luxurious.");
	strcpy(locations[13].long_desc, "This is the master bedroom. Two huge windows look out over the side yard to the north "
		"and let in a surpising amount of afternoon sunlight. You can see the trees blowing in the wind and faintly make "
		"out the neighboring apartment building. A king sized bed, carved out of ebony, sits against the west wall. It "
		"looks so comfortable you could almost take a nap in it right now. A wooden dresser rests against the east wall. "
		"There is also a large antique mirror sitting on top. Oddly, unlike most of the other bedrooms, this one lacks a "
		"closet of any type.");

	//Pink bedroom
	locations[14].west = &locations[12]; //east wing hall
	locations[14].northwest = &locations[15]; //pink bedroom closet
	strcpy(locations[14].name, "Pink bedroom");	
	strcpy(locations[14].short_desc, "You are in the pink bedroom.");
	strcpy(locations[14].long_desc, "You stand in the pink bedroom. An odd light fixture that looks to be carved out of plaster "
		"houses two lights. Old style pull down shades can be found at the top of the windows. You can see far to the east "
		"being at the top of the hill, with much of the town visible in the distance. You also get a north view out two "
		"tiny windows, allowing you to see the next door apartment building. Pink flowers adorn the walls and a wooden "
		"bed painted pink can be found in this room, along with a matching pink dresser with oval beveled mirror. You "
		"imagine that this must have been your aunt's bedroom when she was a little girl.");

	//Pink bedroom closet
	locations[15].southeast = &locations[14]; //pink bedroom
	strcpy(locations[15].name, "Pink bedroom closet");	
	strcpy(locations[15].short_desc, "The pink bedroom's walk in closet");
	strcpy(locations[15].long_desc, "You stumble your way into the walk in closet. Devoid of windows or lights, it is hard to "
		"see anything in here. You used to hide out in here when you were younger as nobody would go looking for you here.");

	//Front bedroom
	locations[16].northwest = &locations[12]; //east wing hall
	locations[16].south = &locations[17]; //front bedroom closet
	strcpy(locations[16].name, "Front bedroom");	
	strcpy(locations[16].short_desc, "You are in the front bedroom.");
	strcpy(locations[16].long_desc, "You are in the front bedroom, although it is currently not used as a bedroom. Various "
		"machinery used for building and repairing shoes can be found here. The only semblance of this being a bedroom is that this "
		"room has a closet to the south. You aren't sure how any of the shoe making equipment works, only that your grandfather "
		"does much of his work here on a freelance basis.");

	//Front bedroom closet
	locations[17].north = &locations[16]; //front bedroom
	strcpy(locations[17].name, "Front bedroom closet");	
	strcpy(locations[17].short_desc, "You are in the front bedroom closet");
	strcpy(locations[17].long_desc, "You are in the front bedroom closet. This one is unique among all the walk in closets "
		"for several reasons. It has a large window in the wall facing south towards the estate next door. It "
		"also has a loveseat built into the wall in case you wanted to sit down. You feel like this may have been "
		"renovated at some time in the past, resulting in it's present appearance."); 		 
	
	//Side bedroom
	locations[18].north = &locations[12]; //east wing hall
	locations[18].east = &locations[19]; //side bedroom closet	
	strcpy(locations[18].name, "Side bedroom");	
	strcpy(locations[18].short_desc, "You are in the side bedroom");
	strcpy(locations[18].long_desc, "This bedroom has a waterbed that is very comfortable to sleep in, and difficult to escape "
		"from afterwards. It also has an odd patchwork like carpet underneath of it that is only slightly larger than "
		"the footprint of the bed. It's very colorful, with lots of reds and blues in it. A brass light fixture lights the "
		"room, supporting two rods with a light bulb on each end. A poster of our planet as viewed from space hangs on the "
		"east wall.");

	//Side bedroom closet
	locations[19].west = &locations[18]; //side bedroom
	strcpy(locations[19].name, "Side bedroom closet");
	strcpy(locations[19].short_desc, "This is the side bedroom closet");
	strcpy(locations[19].long_desc, "This walk in closet is the darkest. You can barely see anything in here at all. You fumble "
		"around in the darkness and can feel some old clothing, as well as some shoes on the ground.");	

	//Twin bedroom
	locations[20].east = &locations[11]; //West wing hall
	locations[20].south = &locations[21]; //Twin bedroom closet
	strcpy(locations[20].name, "Twin bedroom");
	strcpy(locations[20].short_desc, "This is the twin bedroom");
	strcpy(locations[20].long_desc, "You are in the twin bedroom, so called because two old fashioned twin beds are here. One large "
		"window provides an excellent view of the retirement home next door. Brown flowers on a white background can be seen on "
		"the wallpaper in this room. This is the only room with wall to wall carpeting, the carpet being an orange-brown color "
		"that looks like it came out of the sixties.");

	//Twin bedroom closet
	locations[21].north = &locations[20];
	strcpy(locations[21].name, "Twin bedroom closet");
	strcpy(locations[21].short_desc, "This is the twin bedroom closet");
	strcpy(locations[21].long_desc, "This is the walk in closet for the twin bedroom. Although it is one of the smallest bedrooms, "
		"it has the largest closet, and the only one with a light. You can clearly see the shelves lined with every issue of "
		"Popular Science dating back to 1950. The hardwood floor here is oddly painted, a color reminiscent of melted vanilla "
		"ice cream with a hint of chocolate sauce mixed in.");
	
	//Spare bedroom
	locations[22].southeast = &locations[11]; //West wing hall
	locations[22].down = &locations[8]; //Back vestibule. In reality this trip would be dangerous, but wanted to code a one way trip as an example
	strcpy(locations[22].name, "Spare bedroom");
	strcpy(locations[22].short_desc, "This is the spare bedroom");
	strcpy(locations[22].long_desc, "This spare bedroom has been converted into a storage room. Everything is neatly organized along "
		"shelves on the wall, and you can clearly see the trees separating the back yard from the rest of the town through the "
		"window. There is also an in floor laundry chute to quickly get clothing downstairs to be washed.");

	//Second floor restroom
	locations[23].south = &locations[11]; //West wing hall
	strcpy(locations[23].name, "Second floor restroom");
	strcpy(locations[23].short_desc, "This is the second floor restroom");
	strcpy(locations[23].long_desc, "The second floor restroom has two antique wall sconces showing the room in a pleasant glow, as well "
		"a large north facing window to let in additional sunlight. There is also an antique beveled mirror hanging above the sink.");
	
	//Main attic entryway
	locations[24].down = &locations[11]; //Main attic entryway
	locations[24].southeast = &locations[25];
	locations[24].east = &locations[26];
	strcpy(locations[24].name, "Main attic entryway");
	strcpy(locations[24].short_desc, "This is the main attic entryway");
	strcpy(locations[24].long_desc, "You find yourself at the top of the semi-spiral staircase that takes you into the attic. This area "
		"is seldom used, and years of dust has accumulated in the area. It is also dark and cold, as tall ceilings let all the heat "
		"escape and there is no lighting up here. An old television antenna sits in the center of the room.");

	//Attic side room
	locations[25].northwest = &locations[24]; //main attic entryway
	strcpy(locations[25].name, "Attic side room");
	strcpy(locations[25].short_desc, "A side room in the attic which could make a neat bedroom");
	strcpy(locations[25].long_desc, "You are in a side room in the attic. A single large south facing window lets in incredible amounts "
		"of light. The ceiling is sloped in this room and it feels oddly cosy to be in here. Older looking, less finished "
		"hardwood floors can be found here.");

	//Attic main room
	locations[26].west = &locations[24]; //main attic entryway
	strcpy(locations[26].name, "Attic main room");
	strcpy(locations[26].short_desc, "The main room of the attic");
	strcpy(locations[26].long_desc, "This is the main room of the attic. Pink fiberglass insulation lines the floors here. Silver colored "
		"tubing about one foot in diameter helps carry hot or cold air to other parts of the house. A half moon shaped window provides "
		"the best view of the town to the east. You can see almost all the way to the high school from here.");	
	
	//Basement stairs landing
	locations[27].up = &locations[7]; //side door
	locations[27].west = &locations[28]; //furnace room
	locations[27].east = &locations[29]; //firewood room
	strcpy(locations[27].name, "Basement stairs landing");
	strcpy(locations[27].short_desc, "The bottom of the basement stairs");
	strcpy(locations[27].long_desc, "You've descended the stairs into the very large basement. Many ceiling lights ensure that you never "
		"find yourself in the dark down here. You hear running water to the west. There is a slight musty smell down here, as well as "
		"a strong scent of wood. While this area would make a great storage space, very little is actually stored down here.");

	//Furnace room
	locations[28].east = &locations[27]; //Basement stairs landing
	strcpy(locations[28].name, "Furnace room");
	strcpy(locations[28].short_desc, "You are in the furnace room");
	strcpy(locations[28].long_desc, "This is where the furnace is kept. All manners of pipes and ductwork flow into and out of this room. "
		"You also observe that a tiny stream is running through this room. There is a slight sulfurous smell in this room that seems "
		"to be coming from the water.");

	//Firewood room
	locations[29].west = &locations[27]; //Basement stairs landing
	locations[29].south = &locations[30]; //basement room 
	strcpy(locations[29].name, "Firewood room");
	strcpy(locations[29].short_desc, "This room is where the firewood is kept");
	strcpy(locations[29].long_desc, "This room has firewood piled up against two of the walls. You feel like there's enough firewood here "
		"to last for a year, although you've only ever seen your family use any over the Christmas holidays.");

	//Basement room
	locations[30].north = &locations[29];
	strcpy(locations[30].name, "Basement room");
    strcpy(locations[30].short_desc, "A small basement room full of empty chemical bottles");
	strcpy(locations[30].long_desc, "This small basement room has various cans of solvents, thinners, and fuels, most of which are empty. "
		"It almost feels like this room was used for automotive repair, although there would have been no way to get a vehicle down here. "
		"A tiny dirty window to the east only shows the base of one of the lilac trees on the estate grounds.");

	//garage
	locations[31].east = &locations[8]; //back vestibule
	strcpy(locations[31].name, "Garage");
	strcpy(locations[31].short_desc, "The garage, which currently has no vehicles in it");
	strcpy(locations[31].long_desc, "This is the garage. While there are currently no vehicles in it, there is a freezer in the corner. There "
		"is also a tobagan hanging from the ceiling, however it is out of reach, and you would have no use for it in the summer anyway. "
		"The wooden floors are another peculiarity. They are starting to show their age and they bend and dip down whenever you step on "
		"them. You feel that they could benefit from replacement very soon.");

	//objects that the player can interact with

	// radio
	strcpy(objs[0].name, "radio");	
	objs[0].weight = 10;
	objs[0].location = &locations[23];
	objs[0].id = 23;
	strcpy(objs[0].short_desc, "An old radio that's been in the second floor restroom for many years");
	strcpy(objs[0].long_desc, "An old style radio that's been in your family for over 30 years. It is missing its batteries.");	

	//batteries
	strcpy(objs[1].name, "batteries");
	objs[1].weight = 10;
	objs[1].location = &locations[30];
	objs[1].id = 30; //ids correspond to unique locations, so multiple items can share the same id
	strcpy(objs[1].short_desc, "A simple battery pack");
	strcpy(objs[1].long_desc, "A battery pack that looks like it might fit into an electronic device.");

	//dining room couch
	strcpy(objs[2].name, "couch");
	objs[2].location = &locations[4]; //dining room
	objs[2].id = 4;
	strcpy(objs[2].short_desc, "An old couch upholstered in coarse purple fabric. A floral pattern can be faintly made out in it");
	
	//buffet table
	strcpy(objs[3].name, "buffet");
	objs[3].location = &locations[1]; //ground floor hall 
	objs[3].id = 1;
	strcpy(objs[3].short_desc, "An old wooden buffet table. It's been in your family for many years.");	

	//key (hidden in buffet)
	strcpy(objs[4].name, "key");
	objs[4].weight = 1;
	objs[4].location = &locations[1]; //ground floor hall
	objs[4].id = 1;
	objs[4].hidden = true;
	strcpy(objs[4].short_desc, "An ancient key that looks like it was forged when this house was built.");

	//sprites
	player.id = USHRT_MAX;
	return;
}

