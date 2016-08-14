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


static char * paddle_image = 
	"|"
	"|"
	"|"
	"|"
	"|"
	"|"
	"|";

static char * ball = "O";

sprite_id player_paddle;
sprite_id computer_paddle;
sprite_id ball;

void setup() {
	player_paddle = sprite_create(screen_width() - 1 - PADDLE_WIDTH, screen_height() - 7 / 2,PADDLE_WIDTH, PADDLE_HEIGHT, paddle_image);
	computer_paddle =  sprite_create( 1 + PADDLE_WIDTH, screen_height() - 7 / 2,PADDLE_WIDTH, PADDLE_HEIGHT, paddle_image);
	ball = sprite_create(screen_width() / 2, screen_height() / 2, 1, 1, ball);
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
	draw_string(w - 7, h, "CAB202 Assignment 1 - Pong");
	draw_string(w - 7, h + 1, "Eliot Whalan");
	draw_string(w - 7, h + 2, "n9446800");
	draw_string(w - 7, h + 3, "Controls");
	draw_string(w - 7, h + 4, "wasd - movement");
	draw_string(w - 7, h + 5, "l - next level");
	draw_string(w - 7, h + 6, "h - help");
	show_screen();

}

void process() {
	int w = screen_width(), ph = PADDLE_WIDTH;
	int h = screen_height(), pw = PADDLE_HEIGHT;
}
void cleanup() {

}

int main( void ) {
	setup_screen();

	setup();

	show_screen();

	while (!game_over) {
		process();
		if (update_screen) {
			show_screen();
		}
		timer_pause(DELAY);
	}

	cleanup();
	return 0;
}

