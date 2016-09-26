#include <avr/io.h>
#include "cpu_speed.h"
#include "sprite.h"
#include "lcd.h"
#include "graphics.h"
#include <util/delay.h>
#include <math.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>



char lives = 3;
char score = 0;

void draw_score() {
    char buffer[80];
    sprintf(buffer, "%02d (%d)", score, lives);
    draw_string(0, 0, buffer);

}

int main() {
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
    srand(0x20);



    Sprite snake;
    Sprite food;
    unsigned char snake_bitmap [] = {
        0b11100000,
        0b11100000,
    };
    unsigned char food_bitmap [] = {
        0b11100000,
        0b11100000,
        0b11100000,

    };
    int x = rand() % LCD_X;
    int y = rand() % LCD_Y;
    init_sprite(&snake, 5.0, 25.0, 3, 2, snake_bitmap);
    init_sprite(&food, x, y, 3, 3, food_bitmap);
    snake.dx = 1;
    snake.dy = 1;


    while(1){
        clear_screen();
        draw_score();
        draw_sprite(&snake);
        draw_sprite(&food);


        //sw2
        if(PINF & 0b01000000 ){
        }
        //sw3
        if(PINF & 0b00100000 ){
        }

        // top sw1
        if(PIND & 0b00000010 ){
            snake.y -= snake.dy; 
        }
        
        // right sw1
        if(PIND & 0b00000001 ){
            snake.x += snake.dx; 
        }
        // left sw1
        if(PINB & 0b00000010 ){
            snake.x -= snake.dx; 
        }
        //center sw1
        if(PINB & 0b00000001 ){
        }

        // bottom sw1
        if(PINB & 0b10000000 ){
            snake.y += snake.dy; 
        }
        if (snake.x == -1) {
            snake.x = 84;
        }
        if (snake.x == 85) {
            snake.x = 0;

        }
        if (snake.y == 3) {
            snake.y = 48;
        }
        if (snake.y == 49) {
            snake.y = 4;
        }

        if (snake.y == food.y && snake.x == food.x) {
            score++;

        }
        show_screen();
        _delay_ms(50);



    }


    return 0;
}


