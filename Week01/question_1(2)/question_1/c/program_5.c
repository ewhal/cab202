/*	CAB202: Tutorial 1
*	Question 1 - Program 5
*
*	B.Talbot, February 2016
*	Queensland University of Technology
*/
#include <stdio.h>
#include "cab202_graphics.h"
#include "dummy_library.h"

int main() {
    // Setup the screen
    setup_screen();

    // Print our value for pi
    draw_string(29, 10, "~~~~~~~~~~~~~~~~~~~~");
    draw_string(29, 11, "~~ pi is: X.XXXXX ~~");
    draw_string(29, 12, "~~~~~~~~~~~~~~~~~~~~");
    draw_double(39, 11, get_pi());

    // Show the welcome message and wait indefinitely
    show_screen();
    while(1);

    // Clean up the screen and return (we will NEVER make it here!)
    cleanup_screen();
    return 0;
}
