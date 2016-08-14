#include <stdio.h>

void count_down( void ) {
    //  (a) Display title message
	printf("Reverse order list of integers greater than 88, beginning at 379, stepping by -7.\n");

    //  (b) Declare a counter variable of type int and set the initial value 
    //      to 379
	int counter = 379;

    //  (c) While counter is greater than 88 ...
	while (counter >= 88) {

        //  (d) Display value of counter
		printf("%d\n", counter);


        //  (e) Subtract 7 from counter
		counter = counter - 7;
    }
    //  (f) End of While loop that starts at (c)
}

int main( void ) {
	count_down();
	return 0;
}


