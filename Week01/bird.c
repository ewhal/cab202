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

char * bird_img =
/**/          "   _  "
/**/          "__(.)<"
/**/          "\\___) ";


// (a) Declare global variable: a sprite_id called bird.
sprite_id bird;

void setup(void) {
	// (b) Call sprite_create() to initialise bird.
	bird = sprite_create(0, screen_height() - 3, 6, 3, bird_img);
	
	// (c) Call sprite_turn_to() to set the sprite moving.
	sprite_turn_to(bird, 0.2, -0.4);
	
	// (d) Call sprite_draw() to make sprite visible at the start of the game.
	sprite_draw(bird);
}

// Play one turn of game.
void process(void) {
	// (e) Call sprite_step() to move the sprite.
	sprite_step(bird);

	// (f) Declare variable dx of type double.
	//     Initialise dx by calling sprite_dx to find the current horizontal
	//     step size of the sprite.
	double dx = sprite_dx(bird);

	// (g) Declare variable dy of type double.
	//     Initialise dy by calling sprite_dy to find the current vertical
	//     step size of the sprite.
	double dy = sprite_dy(bird);

	// (h) Add constant acceleration to dy.
	dy += 0.003;

	// (i) Call sprite_turn_to() to update the sprite step vector.
	//     (dx does not change, but we need the updated dy value)
	sprite_turn_to(bird, dx, dy);

	// (j) Clear the terminal window.
	clear_screen();

	// (k) Call sprite_draw() to show the sprite in its new position.
	sprite_draw(bird);
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
