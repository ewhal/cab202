#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <cab202_graphics.h>
#include <cab202_sprites.h>
#include <cab202_timers.h>

int lives = 10;
int score = 0;
int level = 1;
int time = 0;

sprite_id paddle;

void draw_border() {
	// top
	draw_line(0, 0, screen_width()-1, 0, '*');
	draw_line(0, 3, screen_width()-1, 3, '*');
	// bottom
	draw_line(0, screen_height()-1, screen_width()-1, screen_height()-1, '*');

	// left 
	draw_line(0, 0, 0, screen_height()-1, '*');
	// right
	draw_line(screen_width()-1, 0, screen_width()-1, screen_height()-1, '*');
	show_screen();

}

void display_hud() {
	int width = screen_width() / 4;
	draw_formatted(2, 2, " lives: %d", lives);
	draw_formatted(width, 2, " score: %d", score);
	draw_formatted(width * 2, 2, " level: %d", level);
	draw_formatted(width * 3, 2, " Time: (%d)", time);
	show_screen();
}

void debug_hud() {

}

void show_help() {
	int w = screen_width();
	int h = screen_height() / 2;
	clear_screen();
	draw_border();
	draw_string(w / 2, h / 2, "CAB202 Assignment 1 - Pong");
	draw_string(w / 2, h + 1 / 2, "Eliot Whalan");
	draw_string(w / 2, h + 2 / 2, "n9446800");
	show_screen();

}

int main( void ) {
	setup_screen();


	//  (q) Refresh the display.

	show_screen();
	timer_pause(1000);
	show_help();
	draw_border();
	display_hud();

	while ( get_char() >= 0 ) {  /* loop until no chars buffered */ }

	//  (r) Wait for a key-press, and return to the calling function.
	wait_char();
	return 0;
}

