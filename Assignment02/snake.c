#include <avr/io.h>
#include "cpu_speed.h"
#include "sprite.h"
#include "lcd.h"
#include "graphics.h"
#include <util/delay.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>



char lives = 3;
int length = 2;
char score = 0;
char walls = 0;

char new_game = 1;

Sprite *snake;
Sprite food;

unsigned char snake_bitmap [] = {
    0b11100000,
    0b11100000,
    0b11100000,
};

void draw_score() {
    char buffer[80];
    sprintf(buffer, "%02d (%d)", score, lives);
    draw_string(0, 0, buffer);
}

void respawn_food(int seed) {
    srand(seed);

    char x = rand() % LCD_X;
    char y = rand() % LCD_Y;

    for (int i = 1; i <= length; i++) {
        if ((x == snake[i].x && y == snake[i].y )) {
            respawn_food(seed*seed+seed);

        }
    }

    food.x = x;
    food.y = y;


}
void respawn_snake(int seed) {
    srand(seed);
    snake = (Sprite*) realloc(snake, (2*sizeof(Sprite)));

    char x = rand() % LCD_X;
    char y = rand() % LCD_Y;
    
    init_sprite(&snake[0], x, y, 3, 3, snake_bitmap);
    init_sprite(&snake[1], snake[0].x, y-4, 3, 3, snake_bitmap);
}
uint16_t adc_read(uint8_t ch)
{
    // select the corresponding channel 0~7
    // ANDing with '7' will always keep the value
    // of 'ch' between 0 and 7
    ch &= 0b00000111;  // AND operation with 7
    ADMUX = (ADMUX & 0xF8)|ch;     // clears the bottom 3 bits before ORing
 
    // start single conversion
    // write '1' to ADSC
    ADCSRA |= (1<<ADSC);
 
    // wait for conversion to complete
    // ADSC becomes '0' again
    // till then, run loop continuously
    while(ADCSRA & (1<<ADSC));
 
    return (ADC);
}
 

void snake_step() {

    for (int i = 1; i <= length; i++) {
        if (snake[0].x == snake[i].x && snake[0].y == snake[i].y && new_game == 0) {
            lives--;
            length = 2;
            new_game = 1;
            return;

        }
    }

    for (int k = length; k > 0; k--){ 

        snake[k].x = (snake[k-1].x);
        snake[k].y = (snake[k-1].y);

    }

    snake[0].x += snake[0].dx;
    snake[0].y += snake[0].dy;



}

void draw_walls() {

    draw_line(0, LCD_Y/2, LCD_X/2, LCD_Y/2);
    draw_line(LCD_X/2, 7, LCD_X/2, LCD_Y/4);
    draw_line(LCD_X/3, LCD_Y/3*2, LCD_X, LCD_Y/3*2);

    if (snake[0].x >= 0 && snake[0].x <= LCD_X/2 && snake[0].y == LCD_Y/2) {
        lives--;
        new_game = 1;
    }
    if (snake[0].x == LCD_X/2 && snake[0].y >= 7 && snake[0].y <= LCD_Y/4) {
        lives--;
        new_game = 1;

    }

    if (snake[0].y == LCD_Y/3*2 && snake[0].x <= LCD_X && snake[0].x >= LCD_X/3) {
        lives--;
        new_game = 1;

    }


}

void draw_snake() {
    for (int i = 0; i < length; i++) {
        draw_sprite(&snake[i]);
    }

}

int main() {
    ADMUX = (1<<REFS0);
 
    // ADC Enable and pre-scaler of 128
    // 8000000/128 = 62500
    ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
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

   snake = (Sprite*) malloc(2 * sizeof(Sprite));

   snake[0].dx = 0;
   snake[0].dy = 0;

    unsigned char food_bitmap [] = {
        0b11000000,
        0b11000000,

    };


    init_sprite(&food, 42, 12, 2, 2, food_bitmap);
    uint16_t adc_result0;
    int delay = 50;


    while(1){
        clear_screen();
        draw_score();
        if (new_game == 1) {
            respawn_snake(24);
            respawn_food(21221);
        }
        adc_result0 = adc_read(0);      // read adc value at PA0
        if (adc_read < 500) {
            delay = 25;
        }


        draw_snake();
        draw_sprite(&food);

        //sw2
        if(PINF & 0b01000000 ){
            walls = 0;
        }
        //sw3
        if(PINF & 0b00100000 ){
            walls = 1;
        }

        // top sw1
        if(PIND & 0b00000010 ){
            snake[0].dy = -1;
            snake[0].dx = 0;

            new_game = 0;
        }

        // right sw1
        if(PIND & 0b00000001 ){
            snake[0].dy = 0;
            snake[0].dx = 1;
            new_game = 0;
        }
        // left sw1
        if(PINB & 0b00000010 ){
            snake[0].dy = 0;
            snake[0].dx = -1;
            new_game = 0;
        }
        //center sw1
        if(PINB & 0b00000001 ){
        }

        // bottom sw1
        if(PINB & 0b10000000 ){
            snake[0].dy = 1;
            snake[0].dx = 0;
            new_game = 0;
        }

        if (walls == 1) {
            draw_walls();
        }
        if (snake[0].x >= 85) {
            snake[0].x = 0;

        }         
        if (snake[0].y <= 7) {
            snake[0].y = 48;
        }         
        if (snake[0].y >= 49) {
            snake[0].y = 8;
        }         
        if (snake[0].x <= -1) {
            snake[0].x = 84;
        }
    
        if (snake[0].x == food.x && snake[0].y == food.y) {
            if (walls == 1) {
                score += 2;
                length += 2;
            } 
            score++;
            length++;
            respawn_food(score+food.y);
            snake = (Sprite*) realloc(snake, (length)*sizeof(Sprite));

            init_sprite(&snake[length], snake[length-1].x, snake[length-1].y, 3, 3, snake_bitmap);

        }


        snake_step();
        show_screen();
        _delay_ms(delay);



    }


    return 0;
}
