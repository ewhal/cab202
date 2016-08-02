#include "cab202_graphics.h"

void draw_lines(void) {
	draw_line(43, 7, 46, 14, '#');
	draw_line(46, 14, 42, 12, '#');
	draw_line(42, 12, 72, 2, '#');
	draw_line(72, 2, 43, 7, '#');
	show_screen();
}
