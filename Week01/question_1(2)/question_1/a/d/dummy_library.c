/*	CAB202: Tutorial 1
*	Question 1 - Source (implementation) for the dummy library
*
*	B.Talbot, February 2016
*	Queensland University of Technology
*/
#include <stdio.h>
#include "dummy_library.h"

void count_up_to_n(int n) {
    for (int i = 0; i<n; i++) {
        printf(">> %d\n", i+1);
    }
}

void count_down_from_n(int n) {
    for (int i = n; i>0; i--) {
        printf(">> %d\n", i);
    }
}

double get_pi(void) {
    return 3.14159265359f;
}
