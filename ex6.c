#include <stdlib.h>
#include <math.h>
#include <cab202_graphics.h>
#include <cab202_sprites.h>
#include <cab202_timers.h>

// Configuration
#define DELAY (10) /* Millisecond delay between game updates */

// Game state.
bool game_over = false; /* Set this to true when game is over */
bool update_screen = true; /* Set to false to prevent screen update. */

// (a) Declare global variable: a sprite_id called marble.
sprite_id marble;

// Setup game.
void setup( void ) {

	// (b) Call sprite_create() to initialise marble.
	marble = sprite_create(8, screen_height(), 1, 1, "O");
	// (c) Call sprite_turn_to() to set the sprite moving.
	sprite_turn_to(marble, 0.1, 0);
	// (d) Call sprite_draw() to make sprite visible at the start of the game.
	sprite_draw(marble);

}

// Play one turn of game.
void process( void ) {

	// (e) Call sprite_step() to move the sprite one step horizontally.
	sprite_step(marble);

	// (f) Declare variable x of type double.
	//     Initialise x by calling sprite_x to find the current horizontal
	//     location of the sprite.

	double x = sprite_x(marble);
	// Calculate y value, based on x. The parameters are:
	// Horizontal offset: 8,
	// Period: 11,
	// Height: 12.
	// ... Make sure these lines have the correct values when you submit!
	double t = (x - 8) * M_PI / 11;
	double y = screen_height() - 1 - 12 * sqrt(fabs(sin(t)));

	// (g) Call sprite_move_to() to move the sprite to the new (x,y) position.
	//     (x does not change, but we need the new calculated y value)

	sprite_move_to(marble, x, y);
	// (h) Call sprite_draw() to show the sprite in its new position.
	sprite_draw(marble);
}

// Clean up game
void cleanup( void ) {
	// No change is required here.
}

// Program entry point.
int main( void ) {
	setup_screen();
	setup();
	show_screen();

	while ( !game_over ) {
		process();

		if ( update_screen ) {
			show_screen();
		}

		timer_pause( DELAY );
	}

	cleanup();

	return 0;
}

