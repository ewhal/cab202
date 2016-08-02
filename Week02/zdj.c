#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <cab202_graphics.h>
#include <cab202_sprites.h>
#include <cab202_timers.h>

// ADD INCLUDES HERE

// Configuration
#define DELAY (10) /* Millisecond delay between game updates */

#define HERO_WIDTH (5)
#define HERO_HEIGHT (5)
#define ZOMBIE_WIDTH (5)
#define ZOMBIE_HEIGHT (5)

// Game state.
bool game_over = false; /* Set this to true when game is over */
bool update_screen = true; /* Set to false to prevent screen update. */

static char * hero_image =
/**/	"H   H"
/**/	"H   H"
/**/	"HHHHH"
/**/	"H   H"
/**/	"H   H";

static char * zombie_image =
/**/	"ZZZZZ"
/**/	"   Z "
/**/	"  Z  "
/**/	" Z   "
/**/	"ZZZZZ";

static char * msg_image =
/**/	"Goodbye and thank-you for playing ZombieDash Jr."
/**/	"            Press any key to exit...            ";

// (c) Declare a sprite_id called hero.
sprite_id hero;

// (m) Declare a sprite_id called zombie.
sprite_id zombie;

// Setup game.
void setup(void) {
	// Useful variables.
	int w = screen_width(), wh = HERO_WIDTH, wz = ZOMBIE_WIDTH;
	int h = screen_height(), hh = HERO_HEIGHT, hz = ZOMBIE_HEIGHT;

	// (a) Draw the border (setup).
	draw_line( 0, 0, w - 1, 0, '*' );
	draw_line( 0, h-1, w - 1, h-1, '*' );
	draw_line( 0, 0, 0, h-1, '*' );
	draw_line( w-1, 0, w - 1, h-1, '*' );

	// Keep the next line intact.
	show_screen();

	// (d) Set up the hero at the centre of the screen.
	hero = sprite_create( (w-wh)/2, (h-hh)/2, wh, hh, hero_image );

	// (e) Draw the hero.
	sprite_draw( hero );
	
	// Keep the next line intact.
	show_screen();

	// (n)	Set up the zombie at a random location on the screen.
	int xrange = w - wz - 2;
	int yrange = h - hz - 2;
	srand( get_current_time() );
	int zx = rand() % xrange + 1;
	int zy = rand() % yrange + 1;
	zombie = sprite_create( zx, zy, wz, hz, zombie_image );

	// (o) Draw the zombie.
	sprite_draw( zombie );

	// (p) Set the zombie in motion.
	sprite_turn_to ( zombie, 0.2, 0 );
	sprite_turn( zombie, rand() % 360 );

	// Keep the next line intact.
	show_screen();
}

// Play one turn of game.
void process(void) {
	int w = screen_width(), wh = HERO_WIDTH, wz = ZOMBIE_WIDTH;
	int h = screen_height(), hh = HERO_HEIGHT, hz = ZOMBIE_HEIGHT;

	// (f) Get a character code from standard input without waiting.
	int key = get_char();
	
	// (y) Test for end of game.

	// (g)	Get the current screen coordinates of the hero in integer variables 
	//		by rounding the actual coordinates.
	int hx = sprite_x( hero );
	int hy = sprite_y( hero );

	// (h) Move hero left according to specification.
	if ( key == 'a' && hx > 1 ) {
		sprite_move( hero, -1, 0 );
	}

	// (i) Move hero right according to specification.
	else if ( key == 'd' && hx < w - wh - 1) {
		sprite_move( hero, +1, 0 );
	}

	// (j) Move hero up according to specification.

	// (k) Move hero down according to specification.

	// (q.a) Test to move the zombie if key is 'z' or ERROR.
	else if ( key == 'z' || key < 0 ) {
		// (r) Zombie takes one step.
		sprite_step( zombie );

		// (s) Get screen location of zombie.
		int zx = round( sprite_x( zombie ) );
		int zy = round( sprite_y( zombie ) );

		// (t) Get the displacement vector of the zombie.
		double zdx = sprite_dx( zombie );
		double zdy = sprite_dy( zombie );
		bool dir_changed = false;

		// (u) Test to see if the zombie hit the left or right border.
		if ( zx == 0 || zx == w - 5 ) {
			zdx = -zdx;
			dir_changed = true;
		}

		// (v) Test to see if the zombie hit the top or bottom border.
		if ( zy == 0  || zy == h - 5 ) {
			zdy = -zdy;
			dir_changed = true;
		}

		// (w) Test to see if the zombie needs to step back and change direction.
		if ( dir_changed ) {
			sprite_back( zombie );
			sprite_turn_to( zombie, zdx, zdy );
		}

	// (q.b) End else-if test to move the zombie if key is 'z' or negative.
	}
	
	// Leave next line intact
	clear_screen();

	// (b) Draw the border (process).
	draw_line( 0, 0, w - 1, 0, '*' );
	draw_line( 0, h-1, w - 1, h-1, '*' );
	draw_line( 0, 0, 0, h-1, '*' );
	draw_line( w-1, 0, w - 1, h-1, '*' );

	// (l)	Draw the hero.
	sprite_draw( hero );

	// (x)	Draw the zombie.
	sprite_draw( zombie );
}

// Clean up game
void cleanup(void) {
	// STATEMENTS
}

// Program entry point.
int main(void) {
	setup_screen();

	auto_save_screen(true);

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