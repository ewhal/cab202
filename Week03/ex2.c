#include <stdlib.h>
#include <math.h>
#include <cab202_graphics.h>
#include <cab202_sprites.h>
#include <cab202_timers.h>

#define DELAY 10 /* milliseconds */

bool game_over;
bool update_screen = true;

//  (a) Declare a global sprite_id called bomb;
sprite_id bomb;

void setup(void) {
	//  (b) Initialise the bomb to display a 1x1 image consisting of a string
	//      containing a single 'O' character. The sprite should appear at 
	//      initial location (13,7).
	bomb = sprite_create(13, 7, 1, 1, "O");

	//  (c) Declare a double precision floating point variable called dx
	//      and set it equal to the difference between the x-coordinate of the 
	//      star and that of the bomb.
	double dx = 58 - sprite_x(bomb);

	//  (d) Declare a double precision floating point variable called dy
	//      and set it equal to the difference between the y-coordinate of the 
	//      star and that of the bomb.
	double dy = 14 - sprite_y(bomb);

	//  (e) Declare a double precision floating point value called dist
	//      and set it equal to the distance between the bomb and the star.
	//      The distance can be calculated using dx and dy, and applying the 
	//      Theorem of Pythagoras.
	double dist = sqrt(pow(dx, 2) + pow(dy, 2));

	//  (f) Normalise dx and dy by dividing by dist. 
	dx = dx / dist;
	dy = dy / dist;

	//  (g) Multiply dx and dy by the velocity, 0.2 units per time step. 
	dx = dx * 0.2;
	dy = dy * 0.2;

	//  (h) Set the bomb in motion towards the star with step-size (dx, dy). 
	sprite_turn_to(bomb, dx, dy);

	//  (i) Draw the bomb.
	sprite_draw(bomb);

	//  (j) Draw the star at its designated location, (58,14).
	draw_char(58, 14, '*');
}

// Play one turn of game.
void process(void) {
	// Keep the next line intact.
	clear_screen();

	//  (k) Move the bomb forward one step.
	sprite_step(bomb);

	//  (l) Draw the bomb.
	sprite_draw(bomb);

	//  (m) Draw the star at its designated location, (58,14).
	draw_char(58, 14, '*');

	//  (n) Get the position of the bomb on the screen, and compare it to the 
	//      location of the star. If they are both the same, set game_over true.
	if (round(sprite_x(bomb)) == 58 || round(sprite_y(bomb)) == 14) {
		game_over = true;
	}
}

// Clean up game
void cleanup(void) {
	// STATEMENTS
}

// Program entry point.
int main(void) {
	setup_screen();

#if defined(AUTO_SAVE_SCREEN)
	auto_save_screen(true);
#endif

	setup();
	show_screen();

	while ( !game_over ) {
		process();

		if ( update_screen ) {
			show_screen();
		}

		timer_pause(DELAY);
	}

	cleanup();

	return 0;
}

