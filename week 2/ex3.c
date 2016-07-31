#include <cab202_graphics.h>

void draw_border ( void ) {
    // INSERT CODE TO DRAW BORDER HERE
	// top
	draw_line(2, 1, screen_width()-1-4, 1, '*');
	// bottom
	draw_line(2, screen_height()-1-5, screen_width()-1-4, screen_height()-1-5, '*');

	draw_line(2, 1, 2, screen_height()-1-5, '*');
	draw_line(screen_width()-1-4, 1, screen_width()-1-4, screen_height()-1-5, '*');

    // And keep the following line intact!
    show_screen();
}

int main( void ) {
    setup_screen();
    draw_border( );
    wait_char();
    cleanup_screen();
    return 0;
}
