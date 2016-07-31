#include "cab202_graphics.h"

void draw_paddles() {
	int i = screen_width() - 4 - 1;
	int length = 5;
	int left_offset = 2;
	int right_offset = 3;
	int left_k_start = (screen_height() - length)/ 2 + left_offset;
	int right_k_start = (screen_height() - length)/ 2 + right_offset;

	draw_line(3, left_k_start, 3, left_k_start + length - 1, '&');
	draw_line(i, right_k_start, i, right_k_start + length - 1, '&');

	show_screen();
}

int main( void ) {
	setup_screen();

	draw_paddles();

	draw_string( 0, screen_height( ) - 1, "Press any key to finish..." );
	wait_char();
	cleanup_screen();
	return 0;
}
