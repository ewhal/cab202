#include <stdio.h>

void list_integers( void ) {
    //  (a) Print the introductory message
	printf("The integer subrange from 63 to 333...\n");


    //  (b) Declare a counter variable of type int, and initialise it to 41
	int counter = 63;

    //  (c) While the value of the counter is less than or equal to 342
	while (counter <= 333) {
        //  (d) Print the value of the counter
		printf("%d\n", counter);
        //  (e) Add 1 to the counter
		counter++;

	}
    // (f) end of While loop started at (c)
}

int main( void ) {
    list_integers();
    return 0;
}
