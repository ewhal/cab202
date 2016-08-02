/*
*	Graphics.h
*
*	Base-level curses-based graphics library for CAB202, 2016 semester 2.
*
*	Authors:
*	 	Lawrence Buckingham
*
*	$Revision:Sun Jul 24 19:36:39 EAST 2016$
*/

#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>

/*
 *	Screen structure contains the off-screen drawing area in which each
 *	frame of the view is constructed before being flushed to the display.
 *
 *	Members:
 *		width - A non-negative integer which specifies the width of the
 *				screen. When the screen is first initialised, this is
 *				made equal to the width of the terminal window at that time.
 *				Subsequently, it may be changed by override_screen_size or
 *				by fit_screen_to_window.
 *
 *		height - A non-negative integer which specifies the height of the
 *				screen. When the screen is first initialised, this is
 *				made equal to the height of the terminal window at that time.
 *				Subsequently, it may be changed by override_screen_size or
 *				by fit_screen_to_window.
 *
 *		pixels - A two-dimensional (ragged) array of characters containing the
 *				"pixel" data of the display. To access the character at 
 *				location (x,y) of Screen * s, use: 
 *                               s->pixels[y][x]
 */
typedef struct Screen {
	int width;
	int height;
	char ** pixels;
} Screen;

/**
 *	The active screen to which data is added by drawing commands.
 *	The contents of this screen will be rendered into the display
 *	when show_screen() is called.
 */
Screen * zdk_screen;

/**
 *	A backing screen which contains a copy data previously displayed by 
 *	show_screen().
 */
Screen * zdk_prev_screen;

/**
 *	Set up the terminal display for curses-based graphics:
 *	.	Echo is disabled.
 *	.	Keystrokes are reported immediately rather than waiting for Enter.
 *	.	Mouse interactions are turned on.
 *	.	The numeric keypad and arrow keys are enabled.
 */
void setup_screen( void );

/**
 *	Restore the terminal to its normal operational state.
 *	
 *	Notes:
 *	.	Under normal operating circumstances, this function will be called
 *		automatically as part of a clean program termination sequence.
 *	.	Therefore, you will rarely call this function explicitly.
 */
void cleanup_screen( void );

/**
 *	Erases the zdk_screen buffer by filling it with space characters
 *	(ASCII code 32).
 */
void clear_screen( void );

/**
 *	Transfers the contents of the zdk_screen buffer to the curses display
 *	window. The operation is optimised to the extent that only characters which
 *	have changed since the last call to show_screen are emitted.
 *	
 *	The display is double-buffered, so after this, the contents of the 
 *	zdk_screen are copied to the zdk_prev_screen.
 */
void show_screen( void );

/**
 *	Draws the specified symbol at the prescribed (x,y) location in the terminal 
 *	window. The rendered character is added to the zdk_screen buffer, but 
 *	remains unseen until the next invocation of show_screen().
 *
 *	Input:
 *		x		-	The horizontal offset of the location at which the character 
 *					is to be drawn, measuring from left to right, with 0 corresponding 
 *					to the left-most visible character position in the terminal window.
 *
 *		y		-	The vertical offset of the location at which the character
 *					is to be drawn, measuring from top to bottom, with 0 corresponding
 *					to the upper-most visible character position in the terminal window.
 *
 *		value	-	The character code (ASCII) of the symbol to be displayed.
 *
 *	Output: void.
 */
void draw_char( int x, int y, char value );

/**
 *	Draws the specified string, starting at the prescribed (x,y) location in the 
 *	terminal window. The rendered text is added to the zdk_screen buffer, but 
 *	remains unseen until the next invocation of show_screen().
 *
 *	Input:
 *		x		-	The horizontal offset of the location at which the first character 
 *					is to be drawn, measuring from left to right, with 0 corresponding 
 *					to the left-most visible character position in the terminal window.
 *
 *		y		-	The vertical offset of the location at which the first character
 *					is to be drawn, measuring from top to bottom, with 0 corresponding
 *					to the upper-most visible character position in the terminal window.
 *
 *		value	-	The character code (ASCII) of the symbol to be displayed.
 *
 *	Output: void.
 */
void draw_string( int x, int y, char * text );

/**
 *	Draws an integer value, starting at the prescribed (x,y) location in the 
 *	terminal window. The rendered text is added to the zdk_screen buffer, but 
 *	remains unseen until the next invocation of show_screen().
 *
 *	Input:
 *		x		-	The horizontal offset of the location at which the first character 
 *					is to be drawn, measuring from left to right, with 0 corresponding 
 *					to the left-most visible character position in the terminal window.
 *
 *		y		-	The vertical offset of the location at which the first character
 *					is to be drawn, measuring from top to bottom, with 0 corresponding
 *					to the upper-most visible character position in the terminal window.
 *
 *		value	-	The numeric value to be displayed.
 *
 *	Output: void.
 *
 *	Notes:
 *	(1)	This function is logically equivalent to draw_formatted(x, y, "%d", value).
 *	(2) Use draw_formatted() to achieve advanced effects such as justification and padding.
 */
void draw_int( int x, int y, int value );

/**
 *	Draws a floating point value, starting at the prescribed (x,y) location in the 
 *	terminal window. The rendered text is added to the zdk_screen buffer, but 
 *	remains unseen until the next invocation of show_screen().
 *
 *	Input:
 *		x		-	The horizontal offset of the location at which the first character 
 *					is to be drawn, measuring from left to right, with 0 corresponding 
 *					to the left-most visible character position in the terminal window.
 *
 *		y		-	The vertical offset of the location at which the first character
 *					is to be drawn, measuring from top to bottom, with 0 corresponding
 *					to the upper-most visible character position in the terminal window.
 *
 *		value	-	The numeric value to be displayed.
 *
 *	Output: void.
 *
 *	Notes:
 *	(1)	This function is logically equivalent to 
 *			draw_formatted(x, y, "%f", value).
 *
 *	(2) Use draw_formatted() to achieve advanced effects such as justification, 
 *		padding, or hexadecimal representation.
 */
void draw_double( int x, int y, double value );

/**
 *	Draws formatted text, starting at the specified location. The rendered text 
 *	is added to the zdk_screen buffer, but remains unseen until the next 
 *	invocation of show_screen().
 *
 *	Input:
 *		x -	The horizontal offset at which the first character is to be
 *			drawn. See draw_string() for further interpretation of this value.
 *
 *		y -	The vertical offset at which the first character is to be drawn.
 *			See draw_string() for further interpretation of this value.
 *
 *		format - A string which is structured according to the requirements 
 *			of sprintf() which will be used in conjunction with any subsequent 
 *			arguments to generate the text for display.
 *
 *		... - An optional sequence of additional arguments.
 *
 *	Output: void.
 *
 *	Notes:	Total length of generated text must be less than 1000 characters.
 *
 *	See also: Standard library function, sprintf().
 */
void draw_formatted( int x, int y, const char * format, ... );

/**
 *	Draws a line segment from (x1,y1) to (x2,y2) using the specified character.
 *
 *	Input:
 *		(x1,y1) -	The offset coordinates of one endpoint of the line. These 
 *					arguments are interpreted in the same manner as (x,y) of
 *					draw_char().
 *
 *		(x2,y2) -	The offset coordinates of the other endpoint. These 
 *					arguments are interpreted in the same manner as (x,y) of
 *					draw_char().
 *
 *		value -	The symbol that is to be used to construct the line segment.
 *
 *	Output: void.
 */
void draw_line( int x1, int y1, int x2, int y2, char value );

/**
 *	Gets the dimensions of the zdk_screen buffer.
 *
 *	Input:
 *		width - The address of a variable of type int in which the width
 *				of the logical screen will be stored.
 *
 *		height - The address of a variable of type int in which the height
 *				of the logical screen will be stored.
 *
 *	Output: void.
 *
 *	Notes: The following blocks of code are logically equivalent.
 *		(a)		int w, h;
 *				get_screen_size( &w, &h );
 *				
 *		(b)		int w = zdk_screen->width;
 *				int h = zdk_screen->height;
 */
void get_screen_size( int * width, int * height );

/**
 *	Returns the width of the zdk_screen buffer.
 *
 *	Input: void.
 *
 *	Output: The designated value.
 *
 *	Notes: The following blocks of code are logically equivalent.
 *		(a)		int w = screen_width();
 *				
 *		(b)		int w = zdk_screen->width;
 */
int screen_width( void );

/**
 *	Returns the current height of the zdk_screen buffer.
 *
 *	Input: void.
 *
 *	Output: The designated value.
 *
 *	Notes: The following blocks of code are logically equivalent.
 *		(a)		int h = screen_height();
 *				
 *		(b)		int h = zdk_screen->height;
 */
int screen_height( void );

/**
 *	Waits for and returns the next character from the standard input stream.
 *
 *	Input: void.
 *
 *	Output: See get_char() for a full description of the returned characters.
 */
int wait_char( void );

/**
 *	Immediately returns the next character from the standard input stream
 *	if one is available, or ERR if none is present.
 *	
 *	If the save-screen state is true (see auto_save_screen) a record of the 
 *	character returned is emitted to the current save-screen file.
 *
 *	Input: void.
 *
 *	Output: If the current input stream contains a keystroke, the character
 *			code of that key is returned. For regular characters, this will 
 *			be the ASCII code of the key. Extended key codes are reported for
 *			additional characters, such as function keys and arrow keys. In
 *			addition, special codes are returned to signal screen resize and 
 *			mouse events.
 *
 *	See also: <curses.h> for a full list of extended key codes.
 *
 *	Notes:	(Advanced) If the zdk_input_stream is non-null, that stream will be used as a 
 *			source rather than the standard input stream.
 */

int get_char( void );

/**
 *	Saves a screen shot to a file having the designated name. Upon 
 *	successful execution, the contents of designated file has been 
 *	replaced by the contents of the zdk_screen buffer.
 *
 *	Input:
 *		file_name - a string holding the name of the file.
 *
 *	Output: void.
 */

void save_screen( const char * file_name );

/*
 *	Automatically save a screen shot each time show_screen is called
 *	if this is non-zero.
 *
 *	Input:
 *		save_if_true - a boolean value which becomes the new save-screen state.
 *
 *	Notes:
 *		(1)	Whenever the save-screen state switches from false to true, a new file
 *			with a name of the form "zdk_screen.N.txt" is created. Here N is
 *			a sequential number starting from 1. This file will accumulate a copy
 *			of the program interaction until the save-screen state becomes false.
 *
 *		(2) The saved data file can be displayed with the CAB202 Movie Player web
 *			application.
 */

void auto_save_screen( bool save_if_true );

/**
 *	Reallocates zdk_screen and zdk_prev_screen buffers to the designated 
 *	dimensions.
 *
 *	Input:
 *		width - A strictly positive integer which specifies the required
 *				buffer width.
 *
 *		height - A strictly positive integer which specifies the required 
 *				buffer height.
 *
 *	Output: void.
 *
 *	Notes:	This function is provided to support automated testing
 *			of code that adapts to a changing screen size.
 */
void override_screen_size( int width, int height );

/**
 *	Resets the zdk_screen and zdk_prev_screen buffers to match the
 *	dimensions of the terminal window.
 *
 *	Input: void.
 *
 *	Output: void.
 */
void fit_screen_to_window( void );

// ------------------------------------------------------------------
//	Advanced facilities to support automated testing.
// ------------------------------------------------------------------

/**
 *	Override: standard output stream.
 *
 *	An output stream which, if not NULL, will receive a copy of all key
 *	events detected by get_char/wait_char plus copies of all displayed 
 *	screens.
 *
 *	Notes: 
 *	(1)	To enable screen capture automatically, use the
 *		auto_save_screen function rather than attempting to manipulate
 *		this object.
 *	(2)	If you specify an exotic stream such as a memory stream you will
 *		probably have to disable curses functionality.
 */
FILE * zdk_save_stream;

/**
 *	Override: standard input stream.
 *
 *	An input stream which, if not NULL, will replace the standard 
 *	input used by get_char/wait_char as the source of keyboard events.
 *
 *	Note: A similar effect can be achieved by using command-line 
 *	redirection to pipe input from a text file. You may find it
 *	easier to use that rather than attempting to work with this interface.
 */
FILE * zdk_input_stream;

/**
 *	Override: disable all curses functionality
 *
 *	A flag which, if true, blocks curses functionality. Useful mainly in a unit test scenario.
 *	
 *
 *	If you _do_ decide to play with this, the safest path is to set it true 
 *	before calling setup_screen(), and don't change it back to false
 *	until after calling cleanup_screen() at the end of the program run.
 */
bool zdk_suppress_output;

#endif /* GRAPHICS_H_ */
