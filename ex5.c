#include "cab202_graphics.h"

void draw_paddles( void ) {

	// left paddle
	draw_string(3, ((screen_height()/2 ) - 1), "$");
	draw_string(3, ((screen_height()/2 ) + 0), "$");
	draw_string(3, ((screen_height()/2 ) + 1), "$");
	draw_string(3, ((screen_height()/2 ) + 2), "$");
	draw_string(3, ((screen_height()/2 ) + 3), "$");

	// right paddle
	draw_string(screen_width() - 5, screen_height()/2 - 0, "$");
	draw_string(screen_width() - 5, screen_height()/2 - 1, "$");
	draw_string(screen_width() - 5, screen_height()/2 - 2, "$");
	draw_string(screen_width() - 5, screen_height()/2 - 3, "$");
	draw_string(screen_width() - 5, screen_height()/2 - 4, "$");
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
