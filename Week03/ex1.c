#include <stdlib.h>
#include <math.h>
#include <cab202_graphics.h>
#include <cab202_sprites.h>
#include <cab202_timers.h>

#define DELAY 10 /* milliseconds */

bool game_over;
bool update_screen = true;

char * bird_img =
/**/          "   _  "
/**/          "__(.)<"
/**/          "\\___) ";

sprite_id bird;

void setup(void) {
    bird = sprite_create(0, screen_height() - 3, 6, 3, bird_img);
    sprite_turn_to(bird, 0.2, -0.4);
    sprite_draw(bird);
}

// Play one turn of game.
void process(void) {
    // Keep the next line intact.
	sprite_step(bird);
	int w = screen_width(), wz = 6;
	int h = screen_height(), hz = 3;

    //  (a) Insert code here to detect collision with the bottom, left, 
    //		and right bounds of the terminal window. If the bird goes outside 
    //		these boundaries, it must reflect back using the method defined 

    //  (b) [Optional] Modify these two lines _if necessary_ to accommodate the 
    //		modified dynamics introduced by bouncing off walls and floor.
	int x = round(sprite_x(bird));
	int y = round(sprite_y(bird));
    double dx = sprite_dx(bird);
    double dy = sprite_dy(bird);

	if (x < 0) {
		dx = -dx;
	}

	if (x == w - wz) {
		dx = -dx;
	}

	if (y == 1) {
		dy = -dy;
	}

	if (y == h) {
		dy = -dy;
	}



    //  Keep the remainder intact.
    dy += 0.003;
    sprite_turn_to(bird, dx, dy);
    clear_screen();
    sprite_draw(bird);
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
