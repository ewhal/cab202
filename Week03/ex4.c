#include <stdlib.h>
#include <cab202_timers.h>
#include <cab202_graphics.h>

//  (a) Declare four global integer variables, as follows:
//      left - the horizontal location of the left edge of the rectangle
//      top - the vertical location of the top edge of the rectangle
//      cols - the width of the rectangle.
//      rows - the height of the rectangle.

int left;
int top;
int cols;
int rows;

//	(b) Declare a global variable of type char called symbol.
//      This is the character that is to be used to render the outline of the
//      rectangle.
char symbol;

void fill_rect(void) {
	//  (c) Test to see if either of cols or rows is less than 1.
	//      If so, the function should stop immediately and draw nothing.
	if (rows >= 1 && cols >= 1) {
		//  (d) Calculate the x-coordinate of the right-hand side of the rectangle.
		//      Store the value in am integer variable called rect_right.
		int rect_right = left + cols - 1;

		//  (e) Calculate the y coordinate of the bottom edge of the rectangle.
		//      Store the result in an integer variable called rect_base.
		int rect_base = top + rows - 1;
		//  (f) Set up an integer variable called y_ctr which will be used to
		//      iterate from the top of the rectangle to the bottom of the rectangle.
		//      Initially it should be equal to top.

		int y_ctr = top;
		//  (g) Enter a loop that will keep going as long as y_ctr is less than or
		//      equal to rect_base.

		while (rect_base >= y_ctr) {
			//  (h) Draw a horizontal line from left to rect_right, with
			//		y-coordinate equal to y_ctr, using the character specified by
			//		symbol.

			draw_line(left, y_ctr, rect_right, y_ctr, symbol);
			//  (i) Increment y_ctr.
			y_ctr++;

			//  (j) End the loop.

		}

	}
}

int main(void) {
	setup_screen();

	// draw a box.
	left = 1 + rand() % (screen_width() - 1) / 2;
	top = 1 + rand() % (screen_height() - 1) / 2;
	cols = 1 + rand() % (screen_width() - left - 1);
	rows = 1 + rand() % (screen_height() - top - 1);
	symbol = '@';
	clear_screen();
	draw_formatted(0, 0,
			"left: %4d, top: %4d, width: %4d, height: %4d - Press key to continue...",
			left, top, cols, rows
			);
	fill_rect();
	show_screen();
	wait_char();

	// draw a box.
	left = 1 + rand() % (screen_width() - 1) / 2;
	top = 1 + rand() % (screen_height() - 1) / 2;
	cols = 1 + rand() % (screen_width() - left - 1);
	rows = 1 + rand() % (screen_height() - top - 1);
	symbol = '&';
	clear_screen();
	draw_formatted(0, 0,
			"left: %4d, top: %4d, width: %4d, height: %4d - Press key to continue...",
			left, top, cols, rows
			);
	fill_rect();
	show_screen();
	wait_char();

	// draw a box with zero width.
	left = 1 + rand() % (screen_width() - 1) / 2;
	top = 1 + rand() % (screen_height() - 1) / 2;
	cols = 0;
	rows = 1 + rand() % (screen_height() - top - 1);
	symbol = '*';
	clear_screen();
	draw_formatted(0, 0,
			"left: %4d, top: %4d, width: %4d, height: %4d - Press key to continue...",
			left, top, cols, rows
			);
	fill_rect();
	show_screen();
	wait_char();

	// draw a box.
	left = 1 + rand() % (screen_width() - 1) / 2;
	top = 1 + rand() % (screen_height() - 1) / 2;
	cols = 1 + rand() % (screen_width() - left - 1);
	rows = 1 + rand() % (screen_height() - top - 1);
	symbol = '#';
	clear_screen();
	draw_formatted(0, 0,
			"left: %4d, top: %4d, width: %4d, height: %4d - Press key to continue...",
			left, top, cols, rows
			);
	fill_rect();
	show_screen();
	wait_char();

	// draw a box with negative width.
	left = 1 + rand() % (screen_width() - 1) / 2;
	top = 1 + rand() % (screen_height() - 1) / 2;
	cols = -rand() % screen_width();
	rows = 1 + rand() % (screen_height() - top - 1);
	symbol = '!';
	clear_screen();
	draw_formatted(0, 0,
			"left: %4d, top: %4d, width: %4d, height: %4d - Press key to continue...",
			left, top, cols, rows
			);
	fill_rect();
	show_screen();
	wait_char();

	// draw a box.
	left = 1 + rand() % (screen_width() - 1) / 2;
	top = 1 + rand() % (screen_height() - 1) / 2;
	cols = 1 + rand() % (screen_width() - left - 1);
	rows = 1 + rand() % (screen_height() - top - 1);
	symbol = '+';
	clear_screen();
	draw_formatted(0, 0,
			"left: %4d, top: %4d, width: %4d, height: %4d - Press key to continue...",
			left, top, cols, rows
			);
	fill_rect();
	show_screen();
	wait_char();

	// draw a box with zero height.
	left = 1 + rand() % (screen_width() - 1) / 2;
	top = 1 + rand() % (screen_height() - 1) / 2;
	cols = 1 + rand() % (screen_width() - left - 1);
	rows = 0;
	symbol = 'a';
	clear_screen();
	draw_formatted(0, 0,
			"left: %4d, top: %4d, width: %4d, height: %4d - Press key to continue...",
			left, top, cols, rows
			);
	fill_rect();
	show_screen();
	wait_char();

	// draw a box.
	left = 1 + rand() % (screen_width() - 1) / 2;
	top = 1 + rand() % (screen_height() - 1) / 2;
	cols = 1 + rand() % (screen_width() - left - 1);
	rows = 1 + rand() % (screen_height() - top - 1);
	symbol = 'b';
	clear_screen();
	draw_formatted(0, 0,
			"left: %4d, top: %4d, width: %4d, height: %4d - Press key to continue...",
			left, top, cols, rows
			);
	fill_rect();
	show_screen();
	wait_char();

	// draw a box with negative width.
	left = 1 + rand() % (screen_width() - 1) / 2;
	top = 1 + rand() % (screen_height() - 1) / 2;
	cols = 1 + rand() % (screen_width() - top - 1);
	rows = -rand() % screen_height();
	symbol = 'c';
	clear_screen();
	draw_formatted(0, 0,
			"left: %4d, top: %4d, width: %4d, height: %4d - Press key to continue...",
			left, top, cols, rows
			);
	fill_rect();
	show_screen();
	wait_char();

	// draw a box.
	left = 1 + rand() % (screen_width() - 1) / 2;
	top = 1 + rand() % (screen_height() - 1) / 2;
	cols = 1 + rand() % (screen_width() - left - 1);
	rows = 1 + rand() % (screen_height() - top - 1);
	symbol = 'd';
	clear_screen();
	draw_formatted(0, 0,
			"left: %4d, top: %4d, width: %4d, height: %4d - Press key to continue...",
			left, top, cols, rows
			);
	fill_rect();
	show_screen();
	wait_char();

	timer_pause(5000);
	cleanup_screen();
	return 0;
}

