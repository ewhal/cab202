/*	CAB202: Tutorial 1
*	Question 2 - Template
*
*	B.Talbot, February 2016
*	Queensland University of Technology
*/
#include <stdio.h>

int main() {
    // Count from 0 to 12
    printf("\nFROM 0 TO 12:\n");
    // TODO
    for (int i = 0; i <= 12; i++) {
	printf("%d\n", i);
    }

    // Count from 5 to 10
    printf("\nFROM 5 TO 10:\n");
    for (int i = 5; i <= 10; i++) {
	printf("%d\n", i);
    }

    // Count from 5 to 0
    printf("\nFROM 5 to 0:\n");
    // TODO
    for (int i = 5; 0 <= i; i--) {
	printf("%d\n", i);
    }

    // Count in 2's, from 10 to 30
    printf("\nIN 2's, FROM 10 to 30:\n");
    // TODO
    for (int i = 10; i <= 30; i += 2) {
	printf("%d\n", i);
    }

    // Count in 0.25's, from 0 to 2
    printf("\nIN 0.25's, FROM 0 to 2:\n");
    // TODO
    for (float i = 0; i <= 2; i += 0.25) {
	printf("%f\n", i);
    }


    // Return from main
    return 0;
}
