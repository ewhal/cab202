/*  CAB202 Tutorial 9
*	Question 3 - Solution
*
*	B.Talbot, May 2016
*	Queensland University of Technology
*/
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>

#include "lcd.h"
#include "graphics.h"
#include "cpu_speed.h"

/*
* Useful defines you can use in your system time calculations
*/
#define FREQUENCY 8000000.0
#define PRESCALER 256.0

/*
* Function declarations
*/
void init_hardware(void);

void pause_while_pressed(void);
double get_system_time(unsigned int timer_count);

/*
* Main - initialise the hardware and run the code that blocks for button holds,
* yet prints an up to date system time when not blocked.
*/
int main() {
    set_clock_speed(CPU_8MHz);

    // Setup the hardware
    init_hardware();

    // Draw the static information to the screen
    draw_string(17, 12, "INTERRUPTS");
    draw_string(12, 20, "System time:");

    // Run the main loop
    char buff[80];
    double curr_time = 0.0;
    while (1) {
        // Call a debounced button checker
        pause_while_pressed();

        // Get the current system time
        // TODO

        // String-ise the current time, and draw it to the screen
        sprintf(buff, "%5.4f", curr_time);
        draw_string(27, 28, buff);

        // Show the screen and have a short nap
        show_screen();
        _delay_ms(100);
    }

    // We'll never get here...
    return 0;
}

/*
* Function implementations
*/
 void init_hardware(void) {
     // Initialising the LCD screen
     lcd_init(LCD_DEFAULT_CONTRAST);

     // Initalising the push buttons as inputs
     DDRF &= ~((1 << PF5) | (1 << PF6));

     // Initialising the LEDs as outputs
     DDRB |= ((1 << PB2) | (1 << PB3));

     // Setup TIMER1 in "normal" operation mode
     // TODO

     // Set the prescaler for TIMER1 so that the clock overflows every ~2.1 seconds
     // TODO

     // Enable the Timer Overflow Interrupt for TIMER1
     // TODO

     // Globally enable interrupts
     // TODO
 }

 void pause_while_pressed(void) {
     // This function should pause if the right button is pressed, and not return
     // until the button is released
     // TODO
 }

double get_system_time(unsigned int timer_count) {
    // Based on the current count, frequency, and prescaler - return the current
    // count time in seconds
    // TODO
    return 0.0;
}

/*
* Interrupt service routines
*/
ISR(TIMER1_OVF_vect) {
    // Interrupt service routine for TIMER1. Toggle an LED everytime this ISR runs
    // TODO
}
