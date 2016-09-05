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
time_t seconds = 0;
time_t minutes = 0;
time_t delay_count = 0;
time_t new_level_time = 0;

bool game_over = false;
bool update_screen = true;
bool help_hud = true;
bool new_game = true;
sprite_id *top_rails;
sprite_id *bottom_rails;
int MAX_RAILS;

double dx;
double dy;
bool dir_changed = false;


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
		PADDLE_HEIGHT = (screen_width() - 3 -1) / 2;
	}
	player_paddle = sprite_create(screen_width() - 2 - 1 - PADDLE_WIDTH, (screen_height() - PADDLE_HEIGHT) / 2, PADDLE_WIDTH, PADDLE_HEIGHT, paddle_image);

	computer_paddle = sprite_create(2 + PADDLE_WIDTH, (screen_height() - PADDLE_HEIGHT) / 2,PADDLE_WIDTH, PADDLE_HEIGHT, paddle_image);

	ball = sprite_create(screen_width() / 2, screen_height() / 2, 1, 1, ball_image);

	singularity = sprite_create((screen_width() / 2) -1, (screen_height() / 2) - 1 , PADDLE_HEIGHT, 5, singularity_image);


}

sprite_id setup_rail(int x, int y) {
	sprite_id rail = sprite_create(x, y, 1, 1, "=");

	return rail;
}
void setup_rails() {
	MAX_RAILS = screen_width()/2;
	top_rails = calloc(MAX_RAILS, sizeof(sprite_id));
	bottom_rails = calloc(MAX_RAILS, sizeof(sprite_id));

	for (int i = 0; i < MAX_RAILS; i++ ) {
		top_rails[i] = setup_rail((screen_width()/4) + i, screen_height()/3);
		bottom_rails[i] = setup_rail((screen_width()/4) + i, screen_height()/3 * 2);
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
	draw_formatted(width * 3, 1, "* Time: %02d:%02d", minutes, seconds);
	show_screen();
}

void clock() {
	delay_count++;
	if (delay_count == 100) {
		seconds++;
		new_level_time++;
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
    char *text[] = {"CAB202 Assignment 1 - Pong", "Eliot Whalan", "n9446800", 
      "Controls", "jk - movement", "l - next level", "h - help menu", "q - quit", 
      "Press any key to start"};
    for (int i = 0; i <= 8; i++) {
      draw_string(w-9, h+i, text[i]);
    }

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
		help_hud = true;
		delay_count = 0;
	} else {
		game_over = true;

	}
	return;


}
bool sprites_collided(sprite_id sprite_1, sprite_id sprite_2) {
    int sprite_1_top = round(sprite_y(sprite_1)),
        sprite_1_bottom = sprite_1_top + sprite_height(sprite_1) - 1,
        sprite_1_left = round(sprite_x(sprite_1)),
        sprite_1_right = sprite_1_left + sprite_width(sprite_1) - 1;

    int sprite_2_top = round(sprite_y(sprite_2)),
        sprite_2_bottom = sprite_2_top + sprite_height(sprite_2) - 1,
        sprite_2_left = round(sprite_x(sprite_2)),
        sprite_2_right = sprite_2_left + sprite_width(sprite_2) - 1;

    return !(
        sprite_1_bottom < sprite_2_top
        || sprite_1_top > sprite_2_bottom
        || sprite_1_right < sprite_2_left
        || sprite_1_left > sprite_2_right
        );
}

void rails_process() {
	for (int i = 0; i <= MAX_RAILS; i++) {
		if (top_rails[i] != NULL) {
			
			sprite_draw(top_rails[i]);
			if (sprites_collided(ball, top_rails[i])) {
				top_rails[i] = NULL;
				dy = -dy;
				dir_changed = true;
				break;

			} 

		}
		if (bottom_rails[i] != NULL) {

			sprite_draw(bottom_rails[i]);
			if (sprites_collided(ball, bottom_rails[i])) {
				bottom_rails[i] = NULL;
				dy = -dy;
				dir_changed = true;
				break;

			}

		}

	}
	return;

}

void singularity_process() {
	double x_diff = screen_width()/2 - sprite_x(ball);
	double y_diff = screen_height()/2- sprite_y(ball);

	double dist_squared = pow(x_diff, 2) + pow(y_diff, 2);
	dist_squared = 25;

	if (dist_squared < 1e-10) {
		dist_squared = 1e-10;
	}
	double dist = sqrt(dist_squared);

	double a = 1/dist_squared;

	dx = dx + (a * x_diff / dist);
	dy = dy + (a * y_diff / dist);

	double v = sqrt(pow(dx, 2) + pow(dy, 2));
	if (v > 1) {
		dx = dx / v;
		dy = dy / v;
	}
	sprite_turn_to(ball, dx, dy);

}

void process_computer_paddle() {
	int pw = PADDLE_WIDTH;
	int h = screen_height(), ph = PADDLE_HEIGHT;
	int y = round(sprite_y(player_paddle));
	int ball_y = round(sprite_y(ball));

	if (sprites_collided(computer_paddle, ball)) {
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
	return;

}

void process() {
	int w = screen_width();
	int h = screen_height(), ph = PADDLE_HEIGHT;
	int y = round(sprite_y(player_paddle));
	int ball_x = round(sprite_x(ball));
	int ball_y = round(sprite_y(ball));

	char key = get_char();

	dir_changed = false;
	dx = sprite_dx(ball);
	dy = sprite_dy(ball);


	switch (key) {
	case 'h':

		help_hud = true;
		break;
		return;
	case 'q':
		show_gameover();
		break;
		return;
	case 'l':
		if (level < 4) {
			level++;
			new_game = true;
			return;

		}
        if (level == 4) {
          level = 1;
          new_game = true;
          return;
        }
		break;
	case 'k':
		if (y > 3) {

			sprite_move(player_paddle, 0, -1);
		}
		break;

	case 'j':

		if (y < h - ph - 1) {
			sprite_move(player_paddle, 0, +1);

		}
		break;
	}

	switch (level) {
	case 2:
		process_computer_paddle();
		break;

	case 3:
		process_computer_paddle();
		if (new_level_time >= 5) {

			if (sprites_collided(singularity, ball)) {
				singularity_process();

			}
			sprite_draw(singularity);
		}
		break;

	case 4:
		process_computer_paddle();
		if (ball_y == screen_height() / 3 || (screen_height()/3 * 2)) {
			rails_process();

		}
		break;

	}


	if (ball_y == 2 || ball_y == h - 1) {
		dy = -dy;
		dir_changed = true;
	}
	if (ball_x == 0) {
		dx = -dx;
		dir_changed = true;
	}



	if (sprites_collided(player_paddle, ball)) {
        if (ball_y == y) {
            dy = -dy;
			dx = -dx;
            dir_changed = true;
			score++;

        } else if (ball_y == y + sprite_height(player_paddle) - 1) {
            dy = -dy;
            dir_changed = true;
			score++;
			dx = -dx;

        } else {
			score++;
			dx = -dx;
			dir_changed = true;
        }
	}

	if (ball_x == w - 1) {
		lives = lives - 1;
		new_game = true;
		return;
	}


	if (dir_changed) {
		sprite_back(ball);
		sprite_turn_to(ball, dx, dy);
	}




	sprite_step(ball);

	sprite_draw(player_paddle);
	sprite_draw(ball);

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
			setup();
			int now = get_current_time();
            double angle = rand() % 90 - 45;
			new_level_time = 0;

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

		timer_pause(DELAY);

		if (lives == 0) {
			clear_screen();
			show_gameover();

		}

	}

	cleanup();
	return 0;
}

