/**
 * @file main.c
 * @brief This file contains functions for a text-based adventure game.
 *
 * The functions in this file include utilities for random number generation,
 * string manipulation to represent dates and times, and the main game loop
 * which handles user input and game state updates. It utilizes the curses library
 * for console-based UI rendering.
 */

#include <curses.h>
#include <stdlib.h>
#include <string.h>
#include "globals.h"

extern monster hero;

/**
 * @brief Brief description of roll.
 *
 * @param dice Description of parameter dice.
 * @param max Description of parameter max.
 * @return Description of the return value.
 */
int roll(int dice, int max) {
    int to_return = 0, i = 0;
    for (i = 0; i < dice; i++) {
        to_return = to_return + ((rand() % max) + 1);
    }
    return to_return;
}

/**
 * @brief Brief description of .
 *
 * @param month Description of parameter month.
 * @return Description of the return value.
 */
char *textual_month (int month) {
    char *month_name = malloc(sizeof(char) * 10);
    switch (month) {
        case 0:
            strcpy(month_name, "Spring\0");
            break;
        case 1:
            strcpy(month_name, "Summer\0");
            break;
        case 2:
            strcpy(month_name, "Autumn\0");
            break;
        case 3:
            strcpy(month_name, "Winter\0");
            break;
        default:
            impossible(4);
            strcpy(month_name, "Unknown\0");
            break;
    }
    return month_name;
}

/**
 * @brief Converts an integer representing a weekday into its corresponding string name.
 *
 * This function takes an integer (0-6) and returns a string representing the name of the
 * corresponding weekday. The week starts from Sunday (0) to Saturday (6). If the input
 * is outside this range, it defaults to "Saturday".
 *
 * @param weekday An integer representing the day of the week, where 0 is Sunday and 6 is Saturday.
 * @return A string representing the name of the day.
 */
char *textual_weekday (int weekday) {
    char *day_name = malloc(sizeof(char) * 110);
    switch (weekday) {
        case 0:
            strcpy(day_name, "Sunday\0");
            break;
        case 1:
            strcpy(day_name, "Monday\0");
            break;
        case 2:
            strcpy(day_name, "Tuesday\0");
            break;
        case 3:
            strcpy(day_name, "Wednesday\0");
            break;
        case 4:
            strcpy(day_name, "Thursday\0");
            break;
        case 5:
            strcpy(day_name, "Friday\0");
            break;
        default:
            strcpy(day_name, "Saturday\0");
            break;
    }
    return day_name;
}

/**
 * @brief Returns the ordinal suffix for a given day of the month.
 *
 * This function takes an integer representing a day and returns its corresponding
 * ordinal suffix ("st", "nd", "rd", "th"). It works correctly for numbers 1 to 30.
 * Note: The function does not handle numbers outside the range 1-30.
 *
 * @param day An integer representing the day of the month.
 * @return A string with the ordinal suffix for the given day.
 */
char *ordinal (int month) { //returns the ordinal portion of a number. breaks if number is above 30 or below 1
    char *ordinal_text = malloc(sizeof(char) * 4);
    switch(month) {
        case 1:
        case 21:
            strcpy(ordinal_text, "st\0");
            break;
        case 2:
        case 22:
            strcpy(ordinal_text, "nd\0");
            break;
        case 3:
        case 23:
            strcpy(ordinal_text, "rd\0");
            break;
        default:
            strcpy(ordinal_text, "th\0");
            break;
    }
    return ordinal_text;
}

/**
 * @brief Formats a single-digit number with a leading zero.
 *
 * This function takes an integer and returns a string with a leading zero
 * if the number is less than 10. It's used to format numbers for time or date displays.
 *
 * @param smallnum An integer number to format.
 * @return A string representation of the number, with a leading zero if it's a single digit.
 */
char *fix_small_numbers(int smallnum) {
    char *to_return = malloc(sizeof(char) * 3);
    if (smallnum < 10) {
        sprintf(to_return, "0%d", smallnum);
    }
    else {
        sprintf(to_return, "%d", smallnum);
    }
    strcat(to_return, "\0");
    return to_return;
}

/**
 * @brief The main game loop for handling user inputs and game state updates.
 *
 * This function continuously processes user inputs for game actions, such as moving the hero,
 * looking around, managing inventory, etc. It updates the game state and UI accordingly.
 * The loop continues until the game is exited.
 */
void loop() {
    char todo = '0';
    bool keepRunning = true;  // Flag to control the loop

    while (keepRunning) {
        bool moved = false;
        redraw_screen();
        todo = wgetch(map);

        // Movement commands
        if (todo == 'k') { // Move up
            moved = move_hero(UP);
            valid = true;
        } else if (todo == 'j') { // Move down
            moved = move_hero(DOWN);
            valid = true;
        } else if (todo == 'h') { // Move left
            moved = move_hero(LEFT);
            valid = true;
        } else if (todo == 'l') { // Move right
            moved = move_hero(RIGHT);
            valid = true;
        } else if (todo == 'n') { // Move down and right
            moved = move_hero(DOWNRIGHT);
            valid = true;
        } else if (todo == 'u') { // Move up and right
            moved = move_hero(UPRIGHT);
            valid = true;
        } else if (todo == 'y') { // Move up and left
            moved = move_hero(UPLEFT);
            valid = true;
        } else if (todo == 'b') { // Move down and left
            moved = move_hero(DOWNLEFT);
            valid = true;
        }

        // Non-movement commands
        if (todo == ';') { // Far look
            look();
        } else if (todo == ':') { // Near look
            what_is_here(levels[hero.z][hero.x][hero.y].type);
        } else if (todo == ',') { // Take
            take();
        } else if (todo == 'i') { // Display inventory
            print_inventory();
        } else if (todo == 'q') { // Quit command
            keepRunning = false;  // Exit the loop
        }

        // Post-action checks and UI updates
        checks(moved);
        mvwprintw(stats, 0, 1, "Stamina:\t%d", hero.stamina);
        mvwprintw(stats, 1, 1, "%s, %s %d%s, %d - %d:%s:%s\t", textual_weekday(g_time.weekday), textual_month(g_time.month), g_time.day, ordinal(g_time.day), g_time.year, g_time.hour, fix_small_numbers(g_time.minute), fix_small_numbers(g_time.second));
        update_windows();
    }

    // Cleanup code or final actions before exiting loop, if any
}

/**
 * @brief Entry point for the text-based adventure game.
 *
 * This function is the starting point of the program. It initializes the game environment
 * and then enters the main game loop. The game continues running within the loop function
 * until an exit condition is met. Upon exiting the loop, the program terminates.
 *
 * @return Returns 0 upon successful completion.
 */
int main() {
    init_game();
    loop();
    return 0;
}
