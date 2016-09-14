/*
 *   File: blank.screen.c
 *   Description: C program for the ATMEL AVR microcontroller (ATmega32 chip)
 *   Write charactes on the the screen
 *
 *
 *  Includes (pretty much compulsory for using the Teensy this semester)
 * 	- avr/io.h: port and pin definitions (i.e. DDRB, PORTB, PB1, etc)
 *	- util/delay.h: '_delay_ms()' function
 *	- cpu_speed.h: macros for forcing the CPU speed to 8MHz (nothing else should ever be used!)
 *  - graphics.h: library to interact with the LCD
 */


#include <avr/io.h>
#include <util/delay.h>

#include "graphics.h"

#include "cpu_speed.h"


//wirte the main file
int main(void) {

    // Set the CPU speed to 8MHz (you must also be compiling at 8MHz)
    set_clock_speed(CPU_8MHz);
    
    //initialise the LCD screen
    lcd_init(LCD_DEFAULT_CONTRAST);
    
    //clear any characters that were written on the screen
    clear_screen();
    
    //fill a buffer (array) of charactes with the string "Microcontroller fun begins! - Happy Hacking", in the position x,y
    //array is too big for the screen size
    //draw_string(10,5, "Microcontroller fun begins! - Happy Hacking");
    
    ////array is too big for the screen size, so we break it into 3 parts
     draw_string(5,5,"Microcontroller");
     draw_string(5,15,"fun begins!");
     draw_string(5,25,"Happy Hacking");
    
    
    //write the string on the lcd
    show_screen();
        
   
	return 0;
}
