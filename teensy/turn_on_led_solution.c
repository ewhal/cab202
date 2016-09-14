/* File: turn_on_led_solution.c
 * Description: C program for the ATMEL AVR microcontroller (ATmega32 chip)
 * Turn on Teensy LED with button
 
 * Teensy PewPew
 
 * Includes (pretty much compulsory for using the Teensy this semester)
 * 	- avr/io.h: port and pin definitions (i.e. DDRB, PORTB, PB1, etc)
 *
 *	- cpu_speed.h: macros for forcing the CPU speed to 8MHz (nothing else should ever be used!)
 */

// AVR header file for all registers/pins
#include <avr/io.h>  

#include "cpu_speed.h"


int main(void)
{
    // Set the CPU speed to 8MHz (you must also be compiling at 8MHz)
    set_clock_speed(CPU_8MHz);

    // LED 0 is connected to pin B2 (port B)
	// set PORTB pin 2 for output
	DDRB=0b00000100;
   // turn ON LEDs by sending '1' to pin 2
	PORTB=0b00000100;
	
	return 0;
}
