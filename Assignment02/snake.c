#include <avr/io.h>
#include "cpu_speed.h"
#include "sprite.h"
#include "lcd.h"
#include "graphics.h"
#include <util/delay.h>
#include <math.h>


int main() {
    set_clock_speed(CPU_8MHz);
    lcd_init(LCD_DEFAULT_CONTRAST);


    
    sprite snake;
    sprite_init(snake, 1, 1, 1, 1,  )


    // SW0 and SW1 are connected to pins F6 and F5. Configure all pins as Input(0)
    DDRF = 0b00000000;
    DDRD = 0b00000000;

    // Teensy LED is connected to B2, configure pin 2 as an output(1)
    DDRB = 0b00001100;

    // turn OFF LED initially
    PORTB = 0b00000000;

    clear_screen();
    draw_string(5,5,"Eliot Whalan");
    draw_string(5,15,"n9446800");
    draw_string(5,25,"dpad movement");
    show_screen();
    while(1){
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


