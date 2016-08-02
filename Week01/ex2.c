#include "cab202_graphics.h"

void draw_balls(void) {
	setup_screen();
	draw_char(16, 0, 'O');
	draw_char(28, 0, 'O');
	draw_char(48, 1, 'O');
	draw_char(0, 23, 'O');
	show_screen();
}
