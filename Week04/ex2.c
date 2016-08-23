#include <stdlib.h>
#include <math.h>
#include <cab202_graphics.h>
#include <cab202_sprites.h>
#include <cab202_timers.h>

#define DELAY 10 /* milliseconds */

bool game_over;
bool update_screen = true;

//  (a) Declare a global sprite_id called station, and two global integers
//      called x_star and y_star which will record the position of the star.
sprite_id station;
int x_star, y_star;


void accelerate_station_towards_star(void);

void setup(void) {
	//  (b) Compute the position of the star, which should be placed at the 
	//      centre of the screen. Use integer arithmetic, make no attempt
	//      to round values, and make no assumptions about the screen size.
	//		Hint: screen width divided by 2, screen height divided by 2.

	x_star = screen_width() / 2;
	y_star = screen_height() / 2;
	//  (c) Initialise the station to display a 1x1 image consisting of a string
	//      containing a single '9' character. The sprite should appear at an
	//      initial location which is displaced 8 units to the left 
	//      and 8 units above the star.
	int offset_x = x_star - 8;
	int offset_y = y_star - 8;
	station = sprite_create(offset_x, offset_y, 1, 1, "9");
	//  (d) Declare a double precision floating point variable called dx
	//      and set it equal to the difference between the x-coordinate of the 
	//      star and that of the station.

	double dx = x_star - sprite_x(station);
	double dy = y_star - sprite_y(station);
	//  (e) Declare a double precision floating point variable called dy
	//      and set it equal to the difference between the y-coordinate of the 
	//      star and that of the station.

	//  (f) Declare a double precision floating point value called dist
	//      and set it equal to the distance between the station and the star.
	//      The distance can be calculated using dx and dy, and applying the 
	//      Theorem of Pythagoras.

	double dist = sqrt(pow(dx, 2) + pow(dy, 2));
	//  (g) Normalise dx and dy by dividing them both by dist. 
	dx = dx / dist;
	dy = dy / dist;

	//  (h) Multiply dx and dy by the velocity indicated in Table 1 corresponding
	//      to your particular x- and y- offset values. 

	dx = dx * 0.22;
	dy = dy * 0.22; 
	//  (i) Aim the station in towards the star by setting its step-size to (dx, dy). 
	sprite_turn_to(station, dx, dy);

	//  (j) Turn the station -90 degrees to convert the flight path 
	//		from a suicide dive into an elliptical orbit.
	sprite_turn(station, -90);

	//  (k) Draw the station.
	sprite_draw(station);
	//  (l) Draw the star at its designated location.
	draw_char(x_star, y_star, '*');
}

// Play one turn of game.
void process(void) {
	// Keep the next line intact.
	clear_screen();

	//  (m) Call accelerate_station_towards_star to accelerate the station toward the star.
	accelerate_station_towards_star();
	//  (n) Move the station forward one step.

	sprite_step(station);
	//  (o) Draw the station.

	sprite_draw(station);
	//  (p) Draw the star at its designated location, (x_star, y_star).

	draw_char(x_star, y_star, '*');
}

void accelerate_station_towards_star(void) {
	//  (aa) Get the difference between the x-coordinate of the star and that 
	//      of the station (without rounding) and store it in a double 
	//      precision floating point variable called x_diff. Do the same for
	//      the y-coordinate, and store the result in a variable called y_diff.

	double x_diff = x_star - sprite_x(station);
	double y_diff = y_star - sprite_y(station);
	//  (ab) Use x_diff and y_diff together with the Theorem of Pythagoras to 
	//      calculate the _square of the distance_ from the station to the star. 
	//      Save this value in a double precision floating point variable, 
	//		dist_squared. (_DO NOT_ take the square root in this step.)

	double dist_squared = pow(x_diff, 2) + pow(y_diff, 2);
	//  (ac) Guard against possible division by zero in later calculations. If
	//      dist_squared is less than 1e-10, set it to 1e-10. In a "practical" 
	//		setting the space station would have vaporised before this point 
	//		could be reached. In this simulation, we will allow the station to 
	//		fly past the star (very close).
	if (dist_squared < 1e-10) {
		dist_squared = 1e-10;
	}
	//  (ad) Compute the square root of dist_squared and store it in a double precision
	//      floating point variable called dist. 

	double dist = sqrt(dist_squared);
	//  (ae) Get the current horizontal and vertical step sizes of the station 
	//      and store them in double precision floating point variables called 
	//      dx and dy.
	double dx = sprite_dx(station);
	double dy = sprite_dy(station);

	//  (af) Calculate the magnitude of the acceleration due to the gravity of
	//      the star. This is given by the formula a = GM/dist_squared, where G is the 
	//      universal gravitational constant, M is the mass of the star, and
	//      dist_squared is the square of the distance from the station to the star.
	//      Due to the laws of physics in the simulation, you may use GM = 1.
	//		In Assignment 1, you will have to experiment with different values
	//		of this quantity to get the desired results.

	double a = 1/dist_squared;
	//  (ag) The acceleration must be split between the x and y direction and
	//      added to the horizontal and vertical step sizes. To do this, add 
	//      (a * x_diff / dist) to dx, and add (a * y_diff / dist) to dy.
	dx = dx + (a * x_diff / dist);
	dy = dy + (a * y_diff / dist);
	//  (ah) Now check the speed of the station. It must never exceed the 
	//      speed of light, which we define to be one screen unit per time 
	//      step. Use the Theorem of Pythagoras to find the speed of
	//      station, v, which is calculated from dx and dy.
	//      (_DEFINITELY_ take the square root this time.)  

	double v = sqrt(pow(dx, 2) + pow(dy, 2));
	//  (ai) If the speed of the station is greater than 1, divide both dx
	//      and dy by the speed. This will limit the a maximum velocity of
	//		1 screen unit per time slice. Think of it as retro-rockets being
	//		used to prevent the station from breaking up.
	if (v > 1) {
		dx = dx / v;
		dy = dy / v;
	}
	//  (aj) Turn the station to move with the new dx and dy values.
	sprite_turn_to(station, dx, dy);
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

