/*
*	CAB202 Teensy Library: 'cab202_teensy'
*	graphics.c
*
*	B.Talbot, September 2015
*	Queensland University of Technology
*/
#include <avr/pgmspace.h>
#include "graphics.h"
#include "macros.h"

unsigned char screen_buffer[LCD_BUFFER_SIZE];

/*
 * Function implementations
 */
void show_screen(void) {
	// Reset our position in the LCD RAM
	lcd_position(0,0);

	// Iterate through our buffer and write each byte to the LCD.
	unsigned int i;
	for(i = 0; i < LCD_BUFFER_SIZE; i++){
		lcd_write(LCD_D, screen_buffer[i]);
	}
}

void clear_screen(void) {
	// Set every byte in the buffer to 0b00000000
	unsigned int i;
	for(i = 0; i < LCD_BUFFER_SIZE; i++){
		 screen_buffer[i] = 0;
	}
}
void set_pixel(unsigned char x, unsigned char y, unsigned char value){
	// Sanity check (bad things happen otherwise...)
	if (x >= LCD_X || y >= LCD_Y) {
		return;
	}

	// Calculate the pixel 'subrow', within that LCD row
	unsigned char row = y/8;
	unsigned char subrow = y%8;

	// Set that particular pixel in our screen buffer
	if (value){
		screen_buffer[row*84+x] |= (1 << subrow); 	//Set Pixel
	} else {
		screen_buffer[row*84+x] &= ~(1 << subrow); 	//Clear Pixel
	}
}

void draw_line(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2) {
	if (x1 == x2) {
		// Draw vertical line
		for (int i = y1; (y2 > y1) ? i <= y2 : i >= y2; (y2 > y1) ? i++ : i-- ) {
			set_pixel(x1, i, 1);
		}
	} else if (y1 == y2) {
		// Draw horizontal line
		for (int i = x1; (x2 > x1) ? i <= x2 : i >= x2; (x2 > x1) ? i++ : i-- ) {
			set_pixel(i, y1, 1);
		}
	} else {
		// Get Bresenhaming...
		float dx = x2-x1;
		float dy = y2-y1;
		float err = 0.0;
		float derr = ABS(dy/dx);

		for (int x = x1, y = y1; (dx > 0) ? x<=x2 : x>=x2; (dx > 0) ? x++ : x--) {
			set_pixel(x, y, 1);
			err += derr;
			while (err >= 0.5 && ((dy > 0) ? y<=y2 : y>=y2) ) {
				set_pixel(x, y, 1);
				y += (dy > 0) - (dy < 0);
				err -= 1.0;
			}
		}
	}
}

void draw_char(unsigned char top_left_x, unsigned char top_left_y, char character) {
	int char_width = 5;
	int char_height = 8;

	// loop through each pixel in the character array and plot each one individually
	for (unsigned char i = 0; i<char_width; i++) {
		for (unsigned char j = 0; j<char_height; j++) {
			set_pixel(top_left_x+i, top_left_y+j, (pgm_read_byte(&(ASCII[character - 0x20][i])) & (1 << j)) >> j);
		}
	}
}

void draw_string(unsigned char top_left_x, unsigned char top_left_y, char *characters) {
	unsigned char i = 0;

	// Draw each character until the null terminator is reached
	while (*characters != 0) {
		draw_char(top_left_x+i*5, top_left_y, *(characters));

		// Add a column of spaces here if you want to space out the lettering.
	    // (see lcd.c for a hint on how to do this)

		characters++;
		i++;
	}
}
