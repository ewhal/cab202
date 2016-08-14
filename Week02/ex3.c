#include <cab202_graphics.h>

void draw_border ( void ) {
	int left = 2;
	int right = 4;
	int top = 1;
	int bottom = 5;

	// top
	draw_line(left, top, screen_width()-1-right, top, '*');
	// bottom
	draw_line(left, screen_height()-1-bottom, screen_width()-1-right, screen_height()-1-right, '*');

	// left 
	draw_line(left, top, left, screen_height()-1-bottom, '*');
	// right
	draw_line(screen_width()-1-right, top, screen_width()-1-right, screen_height()-1-right, '*');

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
