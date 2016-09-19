/*	CAB202: Tutorial 8
*	Question 3 - Solution
*
*	B.Talbot, April 2016
*	Queensland University of Technology
*/
#include <stdlib.h>
#include <math.h>

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#include "cpu_speed.h"
#include "lcd.h"
#include "graphics.h"
#include "sprite.h"

/*
* Defines
*/
#define TEST_STRING "CAB202"

/*
* Function implementations - you only have to implement the first three!!!
*/
void lcd_character(char c);
void lcd_string(unsigned char x, unsigned char y, char *s);

void lcd_sprite(Sprite *sprite);

unsigned char* create_bitmap(unsigned char w, unsigned char h);
unsigned char get_character_byte(unsigned char c, unsigned char column_num);

/*
* Main function - this is all done for you... do not modify anything in here to
* get a solution that "appears" to work - you won't get marks.
*/
int main(void) {
	// Set the CPU speed to 8MHz (you must also be compiling at 8MHz)
	set_clock_speed(CPU_8MHz);

	// Lets be lazy and use a constant seed for this one...
	srand(0);

	// Get our data directions set up as we please (everything is an output unless specified...)
	DDRB = 0b01111100;
	DDRF = 0b10011111;
	DDRD = 0b11111100;

	// Initialise the LCD screen
	lcd_init(LCD_DEFAULT_CONTRAST);

	// Run an infinite loop: draw a background, draw a string
	unsigned char demo_num = 0, btns;
	Sprite s;
	init_sprite(&s, 0, 0, 0, 0, NULL);
	while(1) {
		// Create and show the background
		for (int i = 0; i<LCD_BUFFER_SIZE; i++) {
			screen_buffer[i] = rand() % 256;
		}
		draw_string(LCD_X-10, LCD_Y-16, "  ");
		draw_char(LCD_X-10, LCD_Y-8, ' ');
		draw_char(LCD_X-5, LCD_Y-8, '0' + demo_num);
		show_screen();

		// Perform the direct drawing exercise
		switch (demo_num) {
			case 0:
				// Draw a random character in the top left
				lcd_position(0, 0);
				lcd_character(65 + rand() % 26);
				break;
			case 1:
				// Draw the string at a random position
				lcd_string(rand() % 42, rand() % 48, TEST_STRING);
				break;
			case 2:
				// Free any existing bitmap (we are dynamically allocating...)
				if (s.bitmap != NULL) {
					free(s.bitmap);
				}

				// Spit out some random parameters
 				s.width = 5 + rand() % 30;
				s.height = 5 + rand() % 30;
				s.x = rand() % 48;
				s.y = rand() % 12;

				// Dynamically allocate the new sprite based on the parameters
				s.bitmap = create_bitmap(s.width, s.height);

				// Draw the new sprite directly to the LCD
				lcd_sprite(&s);
				break;
		}

		// Wait for a button press release, incrementing the demo number if it
		// was a left button press
		btns = 0;
		while (btns == 0x00) {
			btns = (PINF >> PF5) & 0x03;
		}
		_delay_ms(50);
		while(((PINF >> PF5) & 0x03) > 0x00);
		_delay_ms(50);
		if (btns > 0x01) {
			demo_num = (demo_num+1) % 3;
		}
	}

	// We're never getting here...
	return 0;
}

/*
* Function implementations
*/
void lcd_character(char c) {
	// This function receives a character. It loops through, drawing each of the
	// 5 bytes defined for the character in the ASCII data from ascii_font.h. You
	// can either access this data directly, or use the provided helper function
	// "get_character_byte()". Don't forget the trailing whitespace (byte number
	// 6 at the end)!

	// TODO
}

void lcd_string(unsigned char x, unsigned char y, char *s) {
	// This function receives x and y coordinates, and a null-terminated string.
	// Draw the string at the requested position (using the row that the requested
	// y coordinate lies in).

	// TODO
}

void lcd_sprite(Sprite *s) {
	// This function receives a pointer to a Sprite struct. Use the x, y, width,
	// and height values to draw the bitmap over the top of the relevant bytes in
	// the screen_buffer. Finally, push ONLY the modified bytes directly to the
	// LCD screen.

	// Loop through each "bitmap bit" in the bitmap using the width and height
	// TODO
			// Find the row number in the LCD that this "bitmap bit" is drawn on
			// TODO

			// Find the column in the LCD that this "bitmap bit" is drawn on
			// TODO

			// Combine the above 2, to find the byte number of the corresponding
			// byte in the screen_buffer
			// TODO

			// Figure out the bit number of the byte from the screen_buffer
			// TODO

			// Figure out how many bytes there are per row of the bitmap
			// TODO

			// Figure out which byte of the bitmap our "bitmap bit" resides in
			// TODO

			// Figure out the bit number within the above byte that is the current
			// "bitmap bit"
			// TODO

			// Get the value of this bit from the bitmap
			// TODO

			// Put this value into the screen buffer, and note the byte number
			// within the screen_buffer as modified
			// TODO


	// Send the modified bytes in the buffer directly to the screen
	// TODO
}

unsigned char* create_bitmap(unsigned char w, unsigned char h) {
	// Allocate the memory initialised to 0
	unsigned char byte_w = ceil(w/8.0);
	unsigned char *bitmap = calloc(h*byte_w, sizeof bitmap);

	// Draw our outer rectangle
	for (unsigned char i = 0; i<byte_w; i++) {
		bitmap[i] = 0b11111111;
		bitmap[h*byte_w-i-1] = 0b11111111;
	}
	for (unsigned char i = 0; i<h; i++) {
		bitmap[i*byte_w] |= (1 << 7);
		bitmap[(i+1)*byte_w-1] |= (1 << (8-w%8)%8); // ew...
	}

	// Return our shiny new bitmap
	return bitmap;
}

unsigned char get_character_byte(unsigned char c, unsigned char column_num) {
	// Get the pointer to the byte from program memory and dereference
	return pgm_read_byte(&(ASCII[c - 0x20][column_num]));
}
