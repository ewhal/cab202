/*	CAB202: Tutorial 3
*	Question 3 - Template
*
*	B.Talbot, March 2016
*	Queensland University of Technology
*/
#include <stdbool.h>
#include <stdlib.h>
#include <ncurses.h>

#include "cab202_graphics.h"

/*
* Function declarations:
*	- You must complete 'draw_flipped_arrow()' to draw the flipped array
*/
void draw_flipped_arrow(char arrow[]);

/*
* Main function
*	- Creates the original arrow and displays a start screen (press 'n' to start
*	the game)
*	- Sits in an endless loop that displays either the original or flipped arrow
*	('f' to toggle)
*	- The blocked out section makes it easier to see if you have perfectly flipped
*	the arrow
*/
int main() {
	// Initialise the graphics environment
	setup_screen();

	// Some extra bells and whistles (color to make things easier to see...)
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_WHITE);

	// Initialise variables
	int key_code = 0;
	char arrow[] = 		{ 		'#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ',
								'#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ',
								'#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
								'#', '#', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ',
								'#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ',
								' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ',
								' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ',
								' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ',
								' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ',
								' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
						};

	// Initial screen
	draw_string(30, 10, ">>> Question 3 <<<");
	draw_string(20, 12, "Instructions:");
	draw_string(20, 13, "'f' to toggle between original and flipped");
	draw_string(20, 14, "'n' to start the game");
	refresh();
	while(key_code != 'n') {
		key_code = wait_char();
	}

	// Perform the main loop
	bool flipped = false;
	while (1) {
		// Clear the screen
		clear_screen();

		// Either draw the original or the flipped arrow
		if (flipped) {
			draw_flipped_arrow(arrow);
		} else {
			for (int i = 0; i<10; i++) {
				for (int ii = 0; ii<10; ii++) {
					draw_char(35+i, 7+ii, arrow[i*10 + ii]);
				}
			}
		}

		// Draw the blocking characters and verbose information
		attron(COLOR_PAIR(1));
		for (int i = 0; i<80; i++) {
			for (int ii = 0; ii<24; ii++) {
				if (i < 35 || i > 44 || ii < 7 || ii > 16) {
					draw_char(i, ii, ' ');
				}
			}
		}
		draw_string(0, 0, "Displaying: ");
		if (flipped) {
			draw_string(15, 0, "FLIPPED");
		} else {
			draw_string(15, 0, "ORIGINAL");
		}
		attroff(COLOR_PAIR(1));

		// Draw and wait for a flip key press
		show_screen();
		key_code = 0;
		while (key_code != 'f') {
			key_code = wait_char();
		}
		flipped = !flipped;
	}

	// Cleanup and exit (although we'll never reach here...)
	cleanup_screen();
	return 0;
}

/*
* Complete your solution to the question here. Notes:
*	- There are two ways you can do this. You can either flip the coordinates or
*	the array indices (the latter is a lot simpler)
*	- Changing the flip should only be a minor modification of 1 line of code
*/
void draw_flipped_arrow(char arrow[]) {
	// TODO
}
