#include "cab202_graphics.h"

void draw_paddles( void ) {
	end 
	draw_line(3, screen_height()/2 + 1, 3, (screen_height()/2) + 5, "$" );
	draw_line(screen_width() - 4, screen_height()/2 + 1, screen_width() - 4 - 1, (screen_height()/2) + 5, "$" );
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
