/*	CAB202: Tutorial 1
*	Question 3 - Template
*
*	B.Talbot, February 2016
*	Queensland University of Technology
*/
#include "cab202_graphics.h"
#include <string.h>

int main() {
	// Setup the screen and display a waiting message
	setup_screen();
	draw_string(27, 11, "Waiting for key press...");
	show_screen();

	// Wait for the key press
	while (1) {
		int key_in = wait_char();

		// Clear the screen
		clear_screen();

		// Draw a word with the character if supported, otherwise print a
		switch (key_in) {
			case 'a':
			case 'A':
				draw_string(27, 11, "apple");
				show_screen();
				break;
			case 'E':
			case 'e':
				draw_string(27, 11, "elephant");
				show_screen();
				break;

			case 'I':
			case 'i':
				draw_string(27, 11, "igloo");
				show_screen();
				break;
			case 'O':
			case 'o':
				draw_string(27, 11, "orange");
				show_screen();
				break;

			case 'U':
			case 'u':
				draw_string(27, 11, "umbrella");
				show_screen();
				break;


			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				draw_string(27, 11, "numbers aren't supported");
				show_screen();
				break;

			default:
				draw_string(27, 11, "error invalid key");
				show_screen();

		}
	}

	// Wait here forever
	cleanup_screen();

	// Clean up the screen and return (we will NEVER make it here!)
	return 0;
}
