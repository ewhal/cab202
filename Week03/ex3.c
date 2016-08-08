#include <cab202_graphics.h>

//  (a) Declare four global integer variables, as follows:
//      horiz - the horizontal location of the left edge of the rectangle
//      vert - the vertical location of the top edge of the rectangle 
//      across - the width of the rectangle.
//      down - the height of the rectangle.

//  (b) Declare a global variable of type char called display_char.
//      This is the character that is to be used to render the rectangle.

void draw_rect ( void ) {
    //  (c) Insert code to draw the outline of the rectangle defined by the global variables.
    //      If either of the width or height is less than or equal to zero,
    //      the function must not draw anything.
}

int main( void ) {
	setup_screen();

    // draw a box.
    horiz = rand() % screen_width() / 2;
    vert = rand() % screen_height() / 2;
    across = 1 + rand() % (screen_width() - horiz - 1);
    down = 1 + rand() % (screen_height() - vert - 1);
    display_char = '@';
    draw_rect();
    show_screen();

    // draw a box.
    horiz = rand() % screen_width() / 2;
    vert = rand() % screen_height() / 2;
    across = 1 + rand() % (screen_width() - horiz - 1);
    down = 1 + rand() % (screen_height() - vert - 1);
    display_char = '&';
    draw_rect();
    show_screen();

    // draw a box with zero width.
    horiz = rand() % screen_width() / 2;
    vert = rand() % screen_height() / 2;
    across = 0;
    down = 1 + rand() % (screen_height() - vert - 1);
    display_char = '*';
    draw_rect();
    show_screen();

    // draw a box.
    horiz = rand() % screen_width() / 2;
    vert = rand() % screen_height() / 2;
    across = 1 + rand() % (screen_width() - horiz - 1);
    down = 1 + rand() % (screen_height() - vert - 1);
    display_char = '#';
    draw_rect();
    show_screen();

    // draw a box with negative width.
    horiz = rand() % screen_width() / 2;
    vert = rand() % screen_height() / 2;
    across = -rand() % screen_width();
    down = 1 + rand() % (screen_height() - vert - 1);
    display_char = '!';
    draw_rect();
    show_screen();

    // draw a box.
    horiz = rand() % screen_width() / 2;
    vert = rand() % screen_height() / 2;
    across = 1 + rand() % (screen_width() - horiz - 1);
    down = 1 + rand() % (screen_height() - vert - 1);
    display_char = '+';
    draw_rect();
    show_screen();

    // draw a box with zero height.
    horiz = rand() % screen_width() / 2;
    vert = rand() % screen_height() / 2;
    across = 1 + rand() % (screen_width() - horiz - 1);
    down = 0;
    display_char = 'a';
    draw_rect();
    show_screen();

    // draw a box.
    horiz = rand() % screen_width() / 2;
    vert = rand() % screen_height() / 2;
    across = 1 + rand() % (screen_width() - horiz - 1);
    down = 1 + rand() % (screen_height() - vert - 1);
    display_char = 'b';
    draw_rect();
    show_screen();

    // draw a box with negative width.
    horiz = rand() % screen_width() / 2;
    vert = rand() % screen_height() / 2;
    across = -rand() % screen_width();
    down = 1 + rand() % (screen_height() - vert - 1);
    display_char = 'c';
    draw_rect();
    show_screen();

    // draw a box.
    horiz = rand() % screen_width() / 2;
    vert = rand() % screen_height() / 2;
    across = 1 + rand() % (screen_width() - horiz - 1);
    down = 1 + rand() % (screen_height() - vert - 1);
    display_char = 'd';
    draw_rect();
    show_screen();

    timer_pause(5000);
	cleanup_screen();
	return 0;
}
