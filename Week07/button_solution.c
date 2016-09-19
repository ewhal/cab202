/* File: button_solution.c
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



int main(void){
    
    // Set the CPU speed to 8MHz (you must also be compiling at 8MHz)
    set_clock_speed(CPU_8MHz);
    
     // SW0 and SW1 are connected to pins F6 and F5. Configure all pins as Input(0)
	 DDRF = 0b00000000;
    
    // Teensy LED is connected to B2, configure pin 2 as an output(1)
     DDRB = 0b00000100;
    
     // turn OFF LED initially
	 PORTB = 0b00000000;
	
    while(1){
         // Read input from PORTF.
         // if Pin F5 changes to high then if condition is true and 
         // an output is ent to Port B pin 2
         if(PINF & 0b00100000 ){
			// Send output to PORTB.
			PORTB = 0b0000100;
		 }
         
        
     }
     return 0;
}
