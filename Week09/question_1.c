#include <avr/io.h>
#include <util/delay.h>

#include "cpu_speed.h"
#include "graphics.h"
#include "lcd.h"
#include "sprite.h"

int main() {
    set_clock_speed(CPU_8MHz);

    //initialise the LCD screen
    lcd_init(LCD_DEFAULT_CONTRAST);

    //clear any characters that were written on the screen
    clear_screen();

    ////array is too big for the screen size, so we break it into 3 parts
    draw_string(5,15,"Eliot Whalan");
    draw_string(5,25,"n9446800");


    unsigned char square_bitmap [] = {
        0b11111111,
        0b11111111,
        0b11111111,
        0b11111111,
        0b11111111,
        0b11111111,
        0b11111111,
        0b11111111,
        0b11111111,

    };
    Sprite square;

    init_sprite(&square, 0, 0, 8, 8, square_bitmap);
    draw_sprite(&square);


    draw_line(LCD_X-1, 0, LCD_X-1, LCD_Y);
    show_screen();

    return 0;
}
