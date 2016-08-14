#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <cab202_graphics.h>
#include <cab202_sprites.h>
#include <cab202_timers.h>

#define DELAY (10)
#define PADDLE_HEIGHT (7)
#define PADDLE_WIDTH (1)

int lives = 10;
int score = 0;
int level = 1;
int time = 0;
bool game_over = false;
bool update_screen = true;
bool help_hud = true;
bool new_game = true;

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
	player_paddle = sprite_create(screen_width() - 2 - PADDLE_WIDTH, (screen_height() - PADDLE_HEIGHT) / 2,PADDLE_WIDTH, PADDLE_HEIGHT, paddle_image);
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
	draw_formatted(width * 3, 2, " Time: (%d)", time);
	show_screen();
}

void debug_hud() {

}

void show_help() {
	int w = screen_width() / 2;
	int h = (screen_height() - 7) / 2;
	draw_string(w - 9, h, "CAB202 Assignment 1 - Pong");
	draw_string(w - 9, h + 1, "Eliot Whalan");
	draw_string(w - 9, h + 2, "n9446800");
	draw_string(w - 9, h + 3, "Controls");
	draw_string(w - 9, h + 4, "ws - movement");
	draw_string(w - 9, h + 5, "l - next level");
	draw_string(w - 9, h + 6, "h - help menu");


}

void process() {
	int w = screen_width(), pw = PADDLE_WIDTH;
	int h = screen_height(), ph = PADDLE_HEIGHT;
	int y = round(sprite_y(player_paddle));
	char key = get_char();
	bool dir_changed = false;

	if (key == 'h' || help_hud == true) {
		show_help();
		show_screen();
		wait_char();
		help_hud = false;
        return;
	}

	clear_screen();
	draw_border();
	display_hud();


	if (new_game) {
		int now = get_current_time();
		srand(now);
		sprite_turn_to(ball, 0.2, 0.0);
		int angle = rand() % 270;
		sprite_turn(ball, angle);
		new_game = false;
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

	int ball_x = round(sprite_x(ball));
	int ball_y = round(sprite_y(ball));

	double dx = sprite_dx(ball);
	double dy = sprite_dy(ball);

	if (ball_y == 3 || ball_y == h - 1) {
		dy = -dy;
		dir_changed = true;
	}

	if (dir_changed) {
		sprite_back(ball);
		sprite_turn_to(ball, dx, dy);
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

	show_screen();

	while (lives != 0) {
		process();
		if (help_hud) {
			help_hud;
		}
		if (update_screen) {
			show_screen();
		}
		timer_pause(DELAY);
	}

	cleanup();
	return 0;
}

