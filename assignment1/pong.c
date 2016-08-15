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
bool debug_on = false;


static char * paddle_image = 
	"|"
	"|"
	"|"
	"|"
	"|"
	"|"
	"|";

static char * ball_image = "O";

sprite_id player_paddle;
sprite_id computer_paddle;
sprite_id ball;

void setup() {
	if (screen_height() < 21) {
		PADDLE_HEIGHT = (screen_width() - 7 -1) / 2;
	}
	player_paddle = sprite_create(screen_width() - 2 - 1 - PADDLE_WIDTH, (screen_height() - PADDLE_HEIGHT) / 2,PADDLE_WIDTH, PADDLE_HEIGHT, paddle_image);
	computer_paddle =  sprite_create( 2 + PADDLE_WIDTH, (screen_height() - PADDLE_HEIGHT )/ 2,PADDLE_WIDTH, PADDLE_HEIGHT, paddle_image);
	ball = sprite_create(screen_width() / 2, screen_height() / 2, 1, 1, ball_image);
}

void draw_border() {
	// top
	draw_line(0, 0, screen_width()-1, 0, '*');
	// top_bottom
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
	draw_formatted(width * 3, 2, " Time: %d:%d", minutes, seconds);
	show_screen();
}

void debug_hud() {
	int width = screen_width() / 4;
	draw_formatted(2, 2, "ball (%d, %d)", round(sprite_x(ball)), round(sprite_y(ball)));
	draw_formatted(width, 2, "paddle (%d, %d)", round(sprite_x(player_paddle)), round(sprite_y(player_paddle)));
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
	for (int i = 3; i > 0; i--) {
		draw_formatted(w, h, "Count Down: %d", i);
		show_screen();
		timer_pause(300);
	}
}

void show_help() {
	int w = screen_width() / 2;
	int h = (screen_height() - 8) / 2;
	draw_string(w - 9, h, "CAB202 Assignment 1 - Pong");
	draw_string(w - 9, h + 1, "Eliot Whalan");
	draw_string(w - 9, h + 2, "n9446800");
	draw_string(w - 9, h + 3, "Controls");
	draw_string(w - 9, h + 4, "jk - movement");
	draw_string(w - 9, h + 5, "l - next level");
	draw_string(w - 9, h + 6, "h - help menu");
	draw_string(w - 9, h + 7, "Press any key");

	show_screen();

}

void process() {
	int w = screen_width(), pw = PADDLE_WIDTH;
	int h = screen_height(), ph = PADDLE_HEIGHT;
	int y = round(sprite_y(player_paddle));
	char key = get_char();
	bool dir_changed = false;

	if (key == 'h' || help_hud == true) {
		show_help();
		wait_char();
		help_hud = false;
        return;
	}

	clock();
	clear_screen();
	draw_border();
	display_hud();


	if (new_game) {
		int now = get_current_time();
		srand(now);

		sprite_turn_to(ball, 0.4, 0.0);
		int angle = rand() % 45;
		sprite_turn(ball, angle);
		count_down();
		new_game = false;
		show_screen();

	}

	if (key == 'w' && y > 4) {
		sprite_move(player_paddle, 0, -1);
	}

	if (key == 's' && y < h - ph - 1) {
		sprite_move(player_paddle, 0, +1);
	}

	if (key == 'l') {
		if (level < 4) {
			level++;
		}
	}

	if (debug_on) {
		debug_hud();
	}

	int ball_x = round(sprite_x(ball));
	int ball_y = round(sprite_y(ball));
	int paddle_x = round(sprite_x(player_paddle));
	int paddle_y = round(sprite_y(player_paddle));

	double dx = sprite_dx(ball);
	double dy = sprite_dy(ball);

	if (ball_y == 3 || ball_y == h - 1) {
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

	if (lives == 0) {
		game_over = true;
		draw_string(w - 9, h, "CAB202 Assignment 1 - Pong");
		wait_char();


	}

	sprite_draw(player_paddle);
//	sprite_draw(computer_paddle);
	sprite_draw(ball);
	sprite_step(ball);


}
void cleanup() {

}

int main( void ) {
	setup_screen();

	setup();

	while (!game_over) {
		process();
		if (update_screen) {
			show_screen();
		}
		delay_count++;
		timer_pause(DELAY);
	}

	cleanup();
	return 0;
}

