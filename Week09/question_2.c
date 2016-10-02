/*	CAB202: Tutorial 8
*	Question 2 - Template
*
*	B.Talbot, April 2016
*	Queensland University of Technology
*/
#include <avr/io.h>
#include <util/delay.h>

#include "cpu_speed.h"
#include "graphics.h"
#include "lcd.h"
#include "sprite.h"

/*
* Function declarations - you only have to touch the first two!!!
*/
unsigned char set_contrast(unsigned char current);
unsigned char set_inversion(unsigned char current);

void create_screen();

/*
* Main function - this is all done for you... no need to modify
*/
int main(void) {
	// Set the CPU speed to 8MHz (you must also be compiling at 8MHz)
	set_clock_speed(CPU_8MHz);

	// Get our data directions set up as we please (everything is an output unless specified...)
	DDRB = 0b01111100;
	DDRF = 0b10011111;
	DDRD = 0b11111100;

	// Initialise the LCD screen
	lcd_init(LCD_DEFAULT_CONTRAST);

	// Let's draw our pretty little set up...
	create_screen();

	// Run our main loop (buttons can change contrast or invert)
	unsigned char btns, mode_inversion = 0, mode_contrast = 1;
	while (1) {
		// Check if we've got a button press
		btns = (PINF >> PF5) & 0x03;
		if (btns > 0x00) {
			// We have a press, wait until it's done
			_delay_ms(50);
			while (((PINF >> PF5) & 0x03) > 0x00);
			_delay_ms(50);

			// Process the press
			if (btns > 0x01) {
				// Left press - change the contrast
				mode_contrast = set_contrast(mode_contrast);
			} else {
				// Right press - toggle the inversion setting
				mode_inversion = set_inversion(mode_inversion);
			}
		}
	}

	// End the program (the screen will remain...)
	return 0;
}

/*
* Function implementations
*/
unsigned char set_contrast(unsigned char current) {
	// Decide on the new enumerated contrast value
	// TODO

	// Set the corresponding contrast (remember to enable and disable extended
	// instruction set)
	// TODO

	// Return the new enumerated contrast value
	return 1; // TODO - it is not return 1...
}

unsigned char set_inversion(unsigned char current) {
	// Set the inversion mode to the opposite of what it currently is
	// TODO

	return 0; // TODO - it is not return 0....
}

void create_screen() {
	// Text
	draw_string(LCD_X/2-20, LCD_Y/2-3, "Hi CAB202");
	show_screen();

	// Top row
	lcd_position(0, 0);
	for (unsigned char i = 0; i<LCD_X; i++) {
		lcd_write(LCD_D, 0xFF);
	}

	// Bottom row
	lcd_position(0, 5);
	for (unsigned char i = 0; i<LCD_X; i++) {
		lcd_write(LCD_D, 0xFF);
	}

	// Left row and right 'rows'
	for (unsigned char i = 1; i<LCD_Y/8-1; i++) {
		for (unsigned char ii = 0; ii < 8; ii++) {
			lcd_position(ii, i);
			lcd_write(LCD_D, 0xFF);
			lcd_position(LCD_X-1-ii, i);
			lcd_write(LCD_D, 0xFF);
		}
	}
}
