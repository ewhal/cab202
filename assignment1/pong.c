#include <cab202_graphics.h>

int level = 1;
int lives = 10;
int time = 0;

int main( void ) {
    setup_screen();
    draw_border( );
    wait_char();
    cleanup_screen();
    return 0;
}

