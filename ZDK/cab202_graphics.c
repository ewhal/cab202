/*
 * cab202_graphics.c
 *
 * Simple character-based "graphics" library for CAB202, 2016 semester 2.
 *
 *	Authors:
 *	 	Lawrence Buckingham
 *	 	Benjamin Talbot
 *
 *	$Revision:Sun Jul 24 19:36:39 EAST 2016$
 */

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <curses.h>
#include <assert.h>
#include "cab202_graphics.h"
#include "cab202_timers.h"

#define ABS(x)	 (((x) >= 0) ? (x) : -(x))
#define MIN(x,y) (((x) < (y)) ? (x) : (y))
#define MAX(x,y) (((x) > (y)) ? (x) : (y))
#define SIGN(x)	 (((x) > 0) - ((x) < 0))

// Global variables to support automated testing.
FILE * zdk_save_stream = NULL;
FILE * zdk_input_stream = NULL;
bool zdk_suppress_output = false;

// Private helper functions.
static void save_screen_(FILE * f);
static void destroy_screen(Screen * scr);
static void save_char(int char_code);

/*
 *	Screen buffers. The most recent screen displayed by show_screen
 *	remains in zdk_prev_screen until the next call to show_screen. The
 *	data that will appear next time show_screen is called is stored
 *	in zdk_screen.
 *
 *	Applications can check these objects for example, to see if a
 *	character has changed, or if something else is already present
 *	at a location.
 */
Screen * zdk_screen = NULL;
Screen * zdk_prev_screen = NULL;

/**
 *	Set up the terminal display for curses-based graphics.
 */
void setup_screen(void) {
	if ( !zdk_suppress_output ) {
		// Enter curses mode.
		initscr();

		// Do not echo keypresses.
		noecho();

		// Turn off the cursor.
		curs_set(0);

		// Cause getch to return ERR if no key pressed within 0 milliseconds.
		timeout(0);

		// Enable the keypad.
		keypad(stdscr, TRUE);

		// Turn on mouse reporting.
		mousemask(ALL_MOUSE_EVENTS, NULL);

		// Erase any previous content that may be lingering in this screen.
		clear();
	}

	// Create buffers
	fit_screen_to_window();

	// Add exit procedure to cleanup the screen before the program exists.
	// Guard to ensure cleanup_screen is added at most once, because in certain
	// situations (e.g. AMS) this function may be called multiple times.
	static bool deja_vu = false;

	if ( !deja_vu ) {
		void ctrl_c_handler(int signal_code);
		signal(SIGINT, ctrl_c_handler);
		atexit(cleanup_screen);
		deja_vu = true;
	}
}

/**
 *	Signal handler for ctrl-c to ensure screen is cleaned up properly.
 */
void ctrl_c_handler(int signal_code) {
	// atexit handler has already been installed, so we should be able to
	// use exit();
	exit(1);
}

/**
*	Restore the terminal to its normal operational state.
*/
void cleanup_screen(void) {
	if ( !zdk_suppress_output ) {
		// cleanup curses.
		endwin();
	}

	// cleanup the drawing buffers.
	destroy_screen(zdk_screen);
	zdk_screen = NULL;

	destroy_screen(zdk_prev_screen);
	zdk_prev_screen = NULL;

	// Close the screen-cast file, if open.
	if ( zdk_save_stream ) {
		fflush(zdk_save_stream);
		fclose(zdk_save_stream);
		zdk_save_stream = NULL;
	}

	// Null the input file (somebody else is responsible for its life cycle).
	if ( zdk_save_stream ) {
		zdk_input_stream = NULL;
	}
}

/**
*	Clear the terminal window.
*/
void clear_screen(void) {
	// Old version: screen was cleared immediately.
	// Clear the curses screen.
	// clear();

	// Erase the contents of the current window.
	if ( zdk_screen != NULL ) {
		int w = zdk_screen->width;
		int h = zdk_screen->height;
		char * scr = zdk_screen->pixels[0];
		memset(scr, ' ', w * h);
	}
}

/**
 *	Make the current contents of the window visible.
 *	If the current view is identical to the previous,
 *	no action is taken (i.e. the curses view is not updated).
 */
void show_screen(void) {
	// Draw parts of the display that are different in the front
	// buffer from the back buffer.
	char ** back_px = zdk_prev_screen->pixels;
	char ** front_px = zdk_screen->pixels;
	int w = zdk_screen->width;
	int h = zdk_screen->height;
	bool changed = false;

	for ( int y = 0; y < h; y++ ) {
		for ( int x = 0; x < w; x++ ) {
			if ( front_px[y][x] != back_px[y][x] ) {
				mvaddch(y, x, front_px[y][x]);
				back_px[y][x] = front_px[y][x];
				changed = true;
			}
		}
	}

	if ( !changed ) {
		return;
	}

	// Save a screen shot, if automatic saves are enabled.
	save_screen_(zdk_save_stream);

	// Force an update of the curses display.
	if ( !zdk_suppress_output ) {
		refresh();
	}
}

/**
 *	Draws the specified character at the prescribed location (x,y) on the window.
 */
void draw_char(int x, int y, char value) {
	if ( zdk_screen != NULL ) {
		int w = zdk_screen->width;
		int h = zdk_screen->height;

		if ( x >= 0 && x < w && y >= 0 && y < h ) {
			zdk_screen->pixels[y][x] = value;
		}
	}
}

void draw_line(int x1, int y1, int x2, int y2, char value) {
	if ( x1 == x2 ) {
		// Draw vertical line
		for ( int i = MIN(y1, y2); i <= MAX(y1, y2); i++ ) {
			draw_char(x1, i, value);
		}
	}
	else if ( y1 == y2 ) {
		// Draw horizontal line
		for ( int i = MIN(x1, x2); i <= MAX(x1, x2); i++ ) {
			draw_char(i, y1, value);
		}
	}
	else {
		// Inserted to ensure that lines are always drawn in the same direction, regardless of
		// the order the endpoints are presented.
		if ( x1 > x2 ) {
			int t = x1;
			x1 = x2;
			x2 = t;
			t = y1;
			y1 = y2;
			y2 = t;
		}

		// Get Bresenhaming...
		float dx = x2 - x1;
		float dy = y2 - y1;
		float err = 0.0;
		float derr = ABS(dy / dx);

		for ( int x = x1, y = y1; (dx > 0) ? x <= x2 : x >= x2; (dx > 0) ? x++ : x-- ) {
			draw_char(x, y, value);
			err += derr;
			while ( err >= 0.5 && ((dy > 0) ? y <= y2 : y >= y2) ) {
				draw_char(x, y, value);
				y += (dy > 0) - (dy < 0);

				err -= 1.0;
			}
		}
	}
}

void draw_string(int x, int y, char * text) {
	for ( int i = 0; text[i]; i++ ) {
		draw_char(x + i, y, text[i]);
	}
}

void draw_int(int x, int y, int value) {
	char buffer[100];
	sprintf(buffer, "%d", value);
	draw_string(x, y, buffer);
}

void draw_double(int x, int y, double value) {
	char buffer[100];
	sprintf(buffer, "%g", value);
	draw_string(x, y, buffer);
}

int get_char() {
	int current_char;

	if ( zdk_input_stream ) {
		current_char = fgetc(zdk_input_stream);
	}
	else {
		current_char = getch();
	}

	save_char(current_char);
	return current_char;
}

int wait_char() {
	int current_char;

	if ( zdk_input_stream ) {
		current_char = fgetc(zdk_input_stream);
	}
	else {
		timeout(-1);
		current_char = getch();
		timeout(0);
	}

	save_char(current_char);
	return current_char;
}

void get_screen_size(int * width, int * height) {
	*width = screen_width();
	*height = screen_height();
}

int screen_width(void) {
	return zdk_screen->width;
}

int screen_height(void) {
	return zdk_screen->height;
}

void save_screen(const char * file_name) {
	FILE * f = fopen(file_name, "a");
	save_screen_(f);
	fclose(f);
}

void save_screen_(FILE * f) {
	if ( f == NULL ) return;

	if ( zdk_screen ) {
		int width = zdk_screen->width;
		int height = zdk_screen->height;

		fprintf(f, "Frame(%d,%d,%f)\n", width, height, get_current_time());

		for ( int y = 0; y < height; y++ ) {
			char * row = zdk_screen->pixels[y];

			for ( int x = 0; x < width; x++ ) {
				fputc(row[x], f);
			}

			fputc('\n', f);
		}

		fprintf(f, "EndFrame\n");
	}
}

/**
 *	Saves the current character to an automatically named local file.
 */

void save_char(int char_code) {
	if ( zdk_save_stream && char_code != ERR ) {
		fprintf(zdk_save_stream, "Char(%d,%f)\n", char_code, get_current_time());
	}
}

/**
 *	This function is provided to support programmatic emulation
 *	of a resized terminal window.
 *	Subsequent calls to screen_width() and screen_height() will
 *	return the supplied values of width and height.
 */

void override_screen_size(int width, int height) {
	void update_buffer(Screen ** buffer, int width, int height);

	update_buffer(&zdk_screen, width, height);
	update_buffer(&zdk_prev_screen, width, height);
}

/**
 *	Private helper function which reallocates and clears the designated buffer.
 *	PRE:	buffer &ne; NULL
 *		AND	width &gt; 0
 *		AND height &gt; 0.
 */

void update_buffer(Screen ** screen, int width, int height) {
	assert(width > 0);
	assert(height > 0);

	if ( screen == NULL ) {
		return;
	}

	Screen * old_screen = (*screen);

	if ( old_screen != NULL && width == old_screen->width && height == old_screen->height ) {
		return;
	}

	Screen * new_screen = calloc(1, sizeof(Screen));

	if ( !new_screen ) {
		*screen = NULL;
		return;
	}

	new_screen->width = width;
	new_screen->height = height;

	new_screen->pixels = calloc(height, sizeof(char *));

	if ( !new_screen->pixels ) {
		free(new_screen);
		*screen = NULL;
		return;
	}

	new_screen->pixels[0] = calloc(width * height, sizeof(char));

	if ( !new_screen->pixels[0] ) {
		free(new_screen->pixels);
		free(new_screen);
		*screen = NULL;
		return;
	}

	for ( int y = 1; y < height; y++ ) {
		new_screen->pixels[y] = new_screen->pixels[y - 1] + width;
	}

	memset(new_screen->pixels[0], ' ', width * height);

	void copy_screen(Screen * old_scr, Screen * new_scr);

	copy_screen(old_screen, new_screen);

	destroy_screen(old_screen);

	(*screen) = new_screen;
}

/**
 *	Copies the data from one screen into the bitmap of another,
 *	clipping to ensure that data is only copied in the smallest
 *	rectangle that fits on both screens.
 *
 *	Input:
 *		src - the address of a Screen from which data is to be copied.
 *		dest - the address of a Screen into which the data is to be copied.
 *
 *	Output: void.
 *
 *	Postcondition:
 *		(src is null OR dest is null OR src is dest ) AND nothing happens;
 *	OR:
 *		The contents of the source screen lying in the area that overlaps
 *		with the destination has been copied into dest at the corresponding
 *		position.
 */

void copy_screen(Screen * src, Screen * dest) {
	if ( src == NULL || dest == NULL || src == dest ) return;

	int clip_width = MIN(src->width, dest->width);
	int clip_height = MIN(src->height, dest->height);

	for ( int y = 0; y < clip_height; y++ ) {
		memcpy(dest->pixels[y], src->pixels[y], clip_width);
	}
}

/**
*	This function is provided to support programmatic emulation
*	of a resized terminal window. It undoes the effects of
*	override_screen_size.
*	Subsequent calls to screen_width() and screen_height() will
*	return the width and height of the current terminal window,
*	respectively.
*/

void fit_screen_to_window(void) {
	if ( zdk_suppress_output ) {
		override_screen_size(80, 24);
	}
	else {
		override_screen_size(getmaxx(stdscr), getmaxy(stdscr));
	}
}

/**
*	Draws formatted text at the specified location.
*	Total length of text must be less than 1000 characters.
*/

void draw_formatted(int x, int y, const char * format, ...) {
	va_list args;
	va_start(args, format);
	char buffer[1000];
	vsprintf(buffer, format, args);
	draw_string(x, y, buffer);
}

/**
 *	Releases all memory allocated to a given Screen.
 *
 *	Parameters:
 *		scr - a (possibly null) pointer to a Screen structure.
 *
 *	Notes: if scr is NULL no action is taken.
 */

void destroy_screen(Screen * scr) {
	if ( scr ) {
		if ( scr->pixels ) {
			if ( scr->pixels[0] ) {
				free(scr->pixels[0]);
			}

			free(scr->pixels);
		}

		free(scr);
	}
}

void auto_save_screen(bool save_if_true) {
	if ( save_if_true && !zdk_save_stream ) {
		char file_name[100];

		// A somewhat arbitrary upper limit on the number of save files.
		for ( int i = 1; i < 1000000; i++ ) {
			sprintf(file_name, "zdk_screen.%d.txt", i);
			FILE * existing_file = fopen(file_name, "r");

			if ( existing_file ) {
				// File exists; leave it alone.
				fclose(existing_file);
			}
			else {
				// File does not exist; use this name.
				break;
			}
		}

		zdk_save_stream = fopen(file_name, "w");
	}
	else if ( zdk_save_stream && !save_if_true ) {
		fflush(zdk_save_stream);
		fclose(zdk_save_stream);
		zdk_save_stream = NULL;
	}
}
