#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <cab202_graphics.h>
#include <cab202_sprites.h>
#include <cab202_timers.h>

#define DELAY (10)
#define PADDLE_WIDTH (1)
int PADDLE_HEIGHT = 7;

int lives = 10;
int score = 0;
int level = 1;
int seconds = 0;
int minutes = 0;
int delay_count = 0;

bool game_over = false;
bool update_screen = true;
bool help_hud = true;
bool new_game = true;
int top_rails[128];
int bottom_rails[128];


static char * paddle_image =
	"|"
	"|"
	"|"
	"|"
	"|"
	"|"
	"|";

static char * ball_image = "O";

static char * singularity_image =
	" \\ | / "
	"  \\|/  "
	"--   --"
	"  /|\\  "
	" / | \\ ";

sprite_id player_paddle;
sprite_id computer_paddle;
sprite_id ball;
sprite_id singularity;

void setup() {
	if (screen_height() < 21) {
		PADDLE_HEIGHT = (screen_width() - 7 -1) / 2;
	}
	player_paddle = sprite_create(screen_width() - 2 - 1 - PADDLE_WIDTH, (screen_height() - PADDLE_HEIGHT) / 2, PADDLE_WIDTH, PADDLE_HEIGHT, paddle_image);

	computer_paddle = sprite_create(2 + PADDLE_WIDTH, (screen_height() - PADDLE_HEIGHT) / 2,PADDLE_WIDTH, PADDLE_HEIGHT, paddle_image);

	ball = sprite_create(screen_width() / 2, screen_height() / 2, 1, 1, ball_image);

	singularity = sprite_create((screen_width() / 2), (screen_height() / 2) - 5, 7, 5, singularity_image);


}
void setup_rails() {
	for (int i = 0; i <=  screen_width()/2; i++ ) {
		top_rails[i] = (screen_width()/4) + i;
		bottom_rails[i] = (screen_width()/4) + i;
	}


}

void draw_border() {
	// top
	draw_line(0, 0, screen_width()-1, 0, '*');

	// top_bottom
	draw_line(0, 2, screen_width()-1, 2, '*');

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
	draw_formatted(2, 1, " lives: %d", lives);
	draw_formatted(width, 1, "* score: %d", score);
	draw_formatted(width * 2, 1, "* level: %d", level);
	draw_formatted(width * 3, 1, "* Time: %2d:%2d", minutes, seconds);
	show_screen();
}

void clock() {
	if (delay_count == 100) {
		seconds++;
		delay_count = 0;
		if (seconds == 60) {
			seconds = 0;
			minutes++;
		}
	}
	return;
}
void count_down() {
	int w = screen_width() / 2;
	int h = screen_height() / 2;
	// todo draw border around count_down
	/*
	//top
	draw_line(0, 0, screen_width()/2-1, 0, '*');

	// bottom
	draw_line(0, screen_height()/2-1, screen_width()/2-1, screen_height()/2-1, '*');

	// left
	draw_line(0, 0, 0, screen_height()/2-1, '*');

	// right
	draw_line(screen_width()/2-1, 0, screen_width()/2-1, screen_height()/2-1, '*');
*/
	for (int i = 3; i > 0; i--) {
		draw_formatted(w, h, "%d", i);
		show_screen();
		timer_pause(300);
	}
}

void show_help() {
	// todo draw border around help menu
	int w = screen_width() / 2;
	int h = (screen_height() - 9) / 2;
	draw_string(w - 9, h, "CAB202 Assignment 1 - Pong");
	draw_string(w - 9, h + 1, "");
	draw_string(w - 9, h + 2, "");
	draw_string(w - 9, h + 3, "Controls");
	draw_string(w - 9, h + 4, "jk - movement");
	draw_string(w - 9, h + 5, "l - next level");
	draw_string(w - 9, h + 6, "h - help menu");
	draw_string(w - 9, h + 7, "q - quit");
	draw_string(w - 9, h + 8, "Press any key");

	show_screen();

}

void show_gameover() {
	int w = screen_width() / 2;
	int h = (screen_height() - 3) / 2;

	draw_string(w - 9, h, "Game over");
	draw_string(w - 9, h + 1, "Play again (y/n): ");

	show_screen();
	char key = wait_char();
	if ( key == 'y') {

		game_over = false;
		new_game = true;
		score = 0;
		minutes = 0;
		seconds = 0;
		level = 1;
		lives = 10;
	} else {
		game_over = true;

	}
	return;


}

// todo clean up
// reduce unneeded code
// break up into functions
// fix up paddle physics
void process() {
	int w = screen_width(), pw = PADDLE_WIDTH;
	int h = screen_height(), ph = PADDLE_HEIGHT;
	int y = round(sprite_y(player_paddle));
	char key = get_char();
	bool dir_changed = false;
	int ball_x = round(sprite_x(ball));
	int ball_y = round(sprite_y(ball));
	int paddle_x = round(sprite_x(player_paddle));
	int paddle_y = round(sprite_y(player_paddle));

	double dx = sprite_dx(ball);
	double dy = sprite_dy(ball);


	if (key == 'h') {
		help_hud = true;
        return;
	}

	if (key == 'q') {
		show_gameover();
		return;
	}

	if (key == 'l') {
		if (level < 4) {
			level++;
			new_game = true;
			setup();
			return;

		}
	}

	if (key == 'k' && y > 3) {
		sprite_move(player_paddle, 0, -1);
	}

	if (key == 'j' && y < h - ph - 1) {
		sprite_move(player_paddle, 0, +1);
	}


	if (level > 1) {
		int computer_paddle_x = round(sprite_x(computer_paddle));
		int computer_paddle_y = round(sprite_y(computer_paddle));

		if (ball_x == computer_paddle_x && ball_y <= computer_paddle_y + (sprite_height(computer_paddle)) && ball_y >= computer_paddle_y) {
			dx = -dx;
			dir_changed = true;

		}

		if (y > 3 && y < h - ph - 1 ) {
			if (ball_y > h - ph - 1) {
				sprite_move_to(computer_paddle, 2 + pw, h - ph - 1);
			} else if (ball_y  <= ph - 1) {
				sprite_move_to(computer_paddle, 2 + pw, 3);
			} else {

				sprite_move_to(computer_paddle, 2 + pw, ball_y - (sprite_height(computer_paddle) / 2) );
			}
		}

		sprite_draw(computer_paddle);
	}

	if (level == 3) {
		if (seconds >= 5 || minutes > 0) {

			// todo use gravity equation
			if (ball_y == screen_height()/2 && ball_x == screen_width()/2 ) {

				dy = -dy * 3;
				dx = -dx * 3;
				dir_changed = true;
			} 
			sprite_draw(singularity);
		}

	}

	if (level == 4) {
		// todo
		// use sprites? clean the hell up
		if (ball_y == screen_height() / 3 || (screen_height()/3 * 2)) {
			for (int i = 0; i <= 128; i++) {
				if (top_rails[i] != 0 || bottom_rails[i] != 0) {

					draw_char(top_rails[i], screen_height()/ 3, '=');
					draw_char(bottom_rails[i], (screen_height()/ 3) * 2, '=');

					if (ball_y == screen_height() / 3 && ball_x == top_rails[i]) {
						top_rails[i] = 0;
						dy = -dy;
						dir_changed = true;
						break;

					} else if (ball_y == screen_height() / 3 * 2 && ball_x == bottom_rails[i] ) {
						bottom_rails[i] = 0;
						dy = -dy;
						dir_changed = true;
						break;

					}
				}

			}

		}

	}

	if (ball_y == 2 || ball_y == h - 1) {
		dy = -dy;
		dir_changed = true;
	}
	if (ball_x == 0) {
		dx = -dx;
		dir_changed = true;
	}

	if (ball_x == w - 1) {
		dx = -dx;
		lives = lives - 1;
		new_game = true;
		setup();
		return;
	}

	if (ball_x == paddle_x && ball_y <= paddle_y + (sprite_height(player_paddle)) && ball_y >= paddle_y) {
		score++;
		dx = -dx;
		dir_changed = true;

	}


	if (dir_changed) {
		sprite_back(ball);
		sprite_turn_to(ball, dx, dy);
	}

	sprite_draw(player_paddle);
	sprite_draw(ball);


	sprite_step(ball);


}
void cleanup() {
	// todo add actual code

}

int main( void ) {
	setup_screen();

	setup();
	setup_rails();

	while (!game_over) {
		// increment the timer
		clock();
		// clear_screen
		clear_screen();

		// draw_borders
		draw_border();

		// display_hud
		display_hud();

		if (help_hud) {
			show_help();
			wait_char();
			help_hud = false;

		}
		if (new_game) {
			int now = get_current_time();
			int angle = rand() % 45;

			srand(now);

			sprite_turn_to(ball, 0.3, 0.0);
			sprite_turn(ball, angle);
			// clear_screen
			clear_screen();

			// draw_borders
			draw_border();

			// display_hud
			display_hud();
			count_down();
			new_game = false;
			show_screen();

		}

		process();

		if (update_screen) {
			show_screen();
		}

		delay_count++;
		timer_pause(DELAY);

		if (lives == 0) {
			clear_screen();
			show_gameover();

		}

	}

	cleanup();
	return 0;
}

