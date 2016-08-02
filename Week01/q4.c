#include "cab202_graphics.h"

int main() {
	setup_screen();
	int width = screen_width();
	int height = screen_height();
	for (int i = -width; i <= width; i += 2) { 
		draw_string(i, height/2, "-");
		show_screen();
	}
	for (int i = -height; i <= height; i += 2) { 
		draw_string(width/2, i, "|");
		show_screen();
	}



	while(1);
	cleanup_screen();

	// Clean up the screen and return (we will NEVER make it here!)
	return 0;
}
