/*  CAB202 Tutorial 9
*	Question 1 - Solution
*
*	B.Talbot, May 2016
*	Queensland University of Technology
*/
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#include "lcd.h"
#include "graphics.h"
#include "cpu_speed.h"

/*
* Global button press count variable - you must update this in your
* check_presses_debounced() function implementation!
*/
int press_count = 0;

/*
* Function declarations
*/
void init_hardware(void);

void check_presses_debounced(void);

/*
* Main - setup everything, then run the main loop
*/
int main() {
    set_clock_speed(CPU_8MHz);

    // Setup the hardware
    init_hardware();

    // Draw the static information to the screen
    draw_string(17, 12, "DEBOUNCING");
    draw_string(12, 20, "Press count:");

    // Run the main loop - check for presses (debounced), print the current count
    char buff[80];
    while (1) {
        // Call a debounced button checker
        check_presses_debounced();

        // Update the count on the screen with the global variable press_count
        sprintf(buff, "%04d", press_count);
        draw_string(32, 28, buff);

        // Show the screen and have a short nap
        show_screen();
        _delay_ms(50);
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
}

void check_presses_debounced(void) {
    // A button press should only be registered ONCE every time that the
    // button is RELEASED. Left decreases the count by 1, right increases the
    // count by 1.
    // TODO
}
