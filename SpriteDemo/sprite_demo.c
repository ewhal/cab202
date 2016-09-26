/*
*	File:	sprite_demo.c
*	Author: Lawrence Buckingham, Queensland University of Technology.
*	Date:	27 April 2015.
*
*	Entry point for the sprite demo program.
*/

#include <avr/io.h> 
#include <util/delay.h> 
#include <graphics.h>
#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "cpu_speed.h"
#include "friendly_ports.h"
#include "one_square.h"
#include "ten_squares.h"
#include "blockhead.h"

void setup_device(void);

int main(void) {
	setup_device();

	draw_string(0, 0, "Hello CAB202!!!");
	show_screen();

	while ( 1 ) {
		play_one_square();
		play_ten_squares();
		walk_the_walk();
	}

	return 0;
}

void setup_device(void) {
	set_clock_speed(CPU_8MHz);

	/**
	* Configure the appropriate data direction register (DDR) to output to the LEDS
	* 	- The LEDs are both on port B (with LED0 on pin 2 and LED1 on pin 3) (see QUT Teensy schematic on Blackboard)
	*	- Therefore, must configure DDR for port B (defined by DDRB from avr/io.h) to output on pins 2 and 3
	*/

	// Note that the symbolic names SW1, SW2, LED0, LED1, LED2 
	// are defined in friendly_ports.h
	DDRB = (LED0 | LED1); // Output to LEDs.
	DDRF = ~(SW1 | SW2);  // Output to LEDs, input from buttons.
	DDRD = LED2;          // Turn on the little yellow LED.

	// Turn everything off to start with
	PORTB = 0x00;
	PORTD = 0x00;

	lcd_init(LCD_DEFAULT_CONTRAST);
	clear_screen();
}
