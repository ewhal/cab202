/*	CAB202: Tutorial 1
*	Question 1 - Program 4
*
*	B.Talbot, February 2016
*	Queensland University of Technology
*/
#include "cab202_graphics.h"

int main() {
    // Setup the screen
    setup_screen();

    // Draw a welcome message
    draw_string(29, 10, "~~~~~~~~~~~~~~~~~~~~");
    draw_string(29, 11, "~~~ Hello CAB202 ~~~");
    draw_string(29, 12, "~~~~~~~~~~~~~~~~~~~~");

    // Show the welcome message and wait indefinitely
    show_screen();
    while(1);

    // Clean up the screen and return (we will NEVER make it here!)
    cleanup_screen();
    return 0;
}
