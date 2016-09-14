/*	CAB202: Tutorial 3
*	Question 2 - Template
*
*	B.Talbot, March 2016
*	Queensland University of Technology
*/
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "cab202_graphics.h"
#include "cab202_timers.h"

#define NUM_BALLS 40

/*
* Function declarations:
*	- You must complete 'move_and_draw_balls()' to move every ball down the amount
*	of spaces in the corresponding element of the 'dy_array[]' array
*	- 'am_i_done()' is complete and checks if all balls are at the bottom - you
*	don't need to touch it
*/
void move_and_draw_balls(int y_array[], int dy_array[]);
bool am_i_done(int y_array[]);

/*
* Main function
*	- Sets up the screen with 40 balls at the top of the screen
*	- While all of the balls aren't at the bottom, 'move_and_draw_balls()' is
*	called every 250ms
* 	- Exits and reports a message based on whether balls went missing or they all
*	reached the bottom
*/
int main() {
	// Seed the random number generator - based off the system clock so it's different every time
	time_t t;
	srand((unsigned) time(&t));

	// Initialise the graphics environment
	setup_screen();

	// Declare the array of ball y coordinates (INITIALISING THEM TO 0), and y displacements
	int ys[NUM_BALLS] = {0};
	int dys[NUM_BALLS];

	// Draw the balls at their starting positions
	for (int i = 0; i<NUM_BALLS; i++) {
		// This is for any screen width
		draw_char(screen_width()/NUM_BALLS*i, ys[i], 'o');

		// You could also stick to static screen width (80)
		//draw_char(i*2, ys[i], 'o');
	}
	show_screen();
	timer_pause(2000);

	// Perform the falling routine, calling the 'move_and_draw_balls()' function
	// with randomly generated displacements
	while(!am_i_done(ys)) {
		// Generate the displacements
		for (int i = 0; i<40; i++) {
			dys[i] = rand() % 3;
		}

		// Move the balls and perform the drawing
		clear_screen();
		move_and_draw_balls(ys, dys);

		// Have a snooze...
		timer_pause(250);
	}

	// Tidy up (provide a verbose message too)
	cleanup_screen();
	if (am_i_done(ys)) {
		printf("All the balls reached the bottom of the screen. Success!\n");
	}
	return 0;
}

/*
* Function implementations
*/
void move_and_draw_balls(int y_array[], int dy_array[]) {
	// TODO move each ball by dy, and draw at the new position. Ensure that they
	// don't go off the bottom of the screen
}

bool am_i_done(int y_array[]) {
	// Loop through the balls, returning false if one is found not at the bottom
	// (this function does not need to be changed)
	for (int i = 0; i<NUM_BALLS; i++) {
		if (y_array[i] != screen_height()-1) {
			return false;
		}
	}
	return true;
}
