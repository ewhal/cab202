#include <avr/io.h>
#include "cpu_speed.h"
#include "sprite.h"
#include "lcd.h"
#include "graphics.h"
#include <util/delay.h>
#include <math.h>
#include <stdio.h>
#include <stdarg.h>



int lives = 3;
int score = 0;

void draw_score() {
    clear_screen();
    char buffer[80];
    sprintf(buffer, "%2d (%d)", score, lives);
    draw_string(0, 0, buffer);
    show_screen();

}

int main() {
    set_clock_speed(CPU_8MHz);
    lcd_init(LCD_DEFAULT_CONTRAST);


    
 //   sprite_id snake;
//    snake = sprite_init(snake, 1, 1, 1, 1,  )


    // SW0 and SW1 are connected to pins F6 and F5. Configure all pins as Input(0)
    DDRF = 0b00000000;
    DDRD = 0b00000000;

    // Teensy LED is connected to B2, configure pin 2 as an output(1)
    DDRB = 0b00001100;

    // turn OFF LED initially
    PORTB = 0b00000000;
        // Set the CPU speed to 8MHz (you must also be compiling at 8MHz)
    set_clock_speed(CPU_8MHz);
    
    //initialise the LCD screen
    lcd_init(LCD_DEFAULT_CONTRAST);
    
    //clear any characters that were written on the screen
    clear_screen();
    
    ////array is too big for the screen size, so we break it into 3 parts
    draw_string(5,15,"Eliot Whalan");
    draw_string(5,25,"n9446800");
    
    
    //write the string on the lcd
    show_screen();
    _delay_ms(2000);
    clear_screen();
    Sprite snake;
    init_sprite(&snake, 5.0, 1.0, 1, 1, '*');


    while(1){
        draw_score();
        draw_sprite(&snake);

        // Read input from PORTF.
        // if Pin F5 changes to high then if condition is true and 
        // an output is ent to Port B pin 2
        if(PINF & 0b01000000 ){
            // Send output to PORTB.
            PORTB = 0b0000100;
        }
        if(PINF & 0b00100000 ){
            // Send output to PORTB.
            PORTB = 0b0001000;
        }
        if(PIND & 0b00000010 ){
            // Send output to PORTB.
            PORTB = 0b0001100;
        }
        if(PIND & 0b00000001 ){
            // Send output to PORTB.
            PORTB = 0b0001000;
        }
        if(PINB & 0b00000010 ){
            // Send output to PORTB.
            PORTB = 0b0000100;
        }
        if(PINB & 0b00000001 ){
            // Send output to PORTB.
            PORTB = 0b0000000;
            PORTB = 0b0001100;
            _delay_ms(500);
        }



        if(PINB & 0b10000000 ){
            // Send output to PORTB.
            PORTB = 0b0000000;
        }



    }


    return 0;
}


