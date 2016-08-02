/*	CAB202: Tutorial 1
*	Question 1 - Program 3
*
*	B.Talbot, February 2016
*	Queensland University of Technology
*/
#include <stdio.h>
#include "dummy_library.h"

int main() {
    // Declare what we are counting up to
    int n = 10;

    // Let's count up to n
    printf("Let's go up to %d...\n", n);
    count_up_to_n(n);

    // And back down again
    printf("and back down again...\n");
    count_down_from_n(n);

    // Return from main
    return 0;
}
