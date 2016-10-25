#include <avr/io.h>
#include "cpu_speed.h"
#include "sprite.h"
#include "lcd.h"
#include "graphics.h"
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
/*
 * snake teensy implmentation
 * Name Eliot Whalan
 * Student Num: n9446800
 */


// use chars to memory
char lives = 3;
int length = 2;
char score = 0;
char walls = 0;

char new_game = 1;

Sprite snake[25];
Sprite food;

unsigned char snake_bitmap [] = {
    0b11100000,
    0b11100000,
    0b11100000,
};

void draw_score() {
    char buffer[80];
    sprintf(buffer, "S: %02d L: (%d)", score, lives);
    draw_string(0, 0, buffer);
}


void respawn_food(int seed) {
    srand(seed);

    char x = rand() % LCD_X;
    char y = rand() % LCD_Y;

    for (int i = 1; i <= length; i++) {
        char snake_top = snake[i].y,
            snake_bottom = snake_top + snake[i].height - 1,
            snake_left = snake[i].x,
            snake_right = snake_left + snake[i].width - 1;

        char food_top = food.y,
            food_bottom = food_top + food.height - 1,
            food_left = food.x,
            food_right = food_left + food.width - 1;

        if (!(snake_bottom < food_top
                || snake_top > food_bottom
                || snake_right < food_left
                || snake_left > food_right
            )) {

            respawn_food(seed+length*score*lives);
        }
    }
    if (y <= 7) {
        respawn_food(seed+length*score*lives);
    } else if (y >= 49) {
        respawn_food(seed+length*score*lives);
    } else if (x <= -1) {
        respawn_food(seed+length*score*lives);
    } else if (x >= 85) {
        respawn_food(seed+length*score*lives);
    } else {
        food.x = x;
        food.y = y;
    }
}

void respawn_snake(int seed) {
    srand(seed);

    char x = rand() % LCD_X;
    char y = rand() % LCD_Y;

    init_sprite(&snake[0], x, y, 3, 3, snake_bitmap);
    init_sprite(&snake[1], snake[0].x, y-4, 3, 3, snake_bitmap);
    snake[0].dx = 0;
    snake[0].dy = 0;
}

uint16_t adc_read(uint8_t ch) {
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
        // check for snake sprite collisions
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

int draw_wall(int x_start, int y_start, int length, int height) {
    int snake_top = snake[0].y,
        snake_bottom = snake_top + snake[0].height - 1,
        snake_left = snake[0].x,
        snake_right = snake_left + snake[0].width - 1;

    int wall_top = y_start,
        wall_bottom = wall_top + height,
        wall_left = x_start,
        wall_right = wall_left + length;

    draw_line(wall_left, wall_top, wall_right, wall_bottom);

    return !(
        snake_bottom < wall_top
        || snake_top > wall_bottom
        || snake_right < wall_left
        || snake_left > wall_right
        );
}

void draw_snake() {
    for (int i = 0; i < length; i++) {
        draw_sprite(&snake[i]);
    }

}

int sprites_collided() {
    int snake_top = snake[0].y,
        snake_bottom = snake_top + snake[0].height - 1,
        snake_left = snake[0].x,
        snake_right = snake_left + snake[0].width - 1;

    int food_top = food.y,
        food_bottom = food_top + food.height - 1,
        food_left = food.x,
        food_right = food_left + food.width - 1;

    return !(
        snake_bottom < food_top
        || snake_top > food_bottom
        || snake_right < food_left
        || snake_left > food_right
        );
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


    respawn_snake(24);

    unsigned char food_bitmap [] = {
        0b11000000,
        0b11000000,

    };


    init_sprite(&food, 42, 12, 2, 2, food_bitmap);
    uint16_t adc_result;

    while(lives != 0){
        clear_screen();
        draw_score();
        if (new_game == 1) {
            respawn_snake(24*length);
            respawn_food(214*length*score);
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
            snake[0].dy = -3;
            snake[0].dx = 0;

            new_game = 0;
        }

        // right sw1
        if(PIND & 0b00000001 ){
            snake[0].dy = 0;
            snake[0].dx = 3;
            new_game = 0;
        }
        // left sw1
        if(PINB & 0b00000010 ){
            snake[0].dy = 0;
            snake[0].dx = -3;
            new_game = 0;
        }

        // bottom sw1
        if(PINB & 0b10000000 ){
            snake[0].dy = 3;
            snake[0].dx = 0;
            new_game = 0;
        }

        if (walls == 1) {
            if (draw_wall(0, LCD_Y/2, 24, 0)) {
                lives--;
                length = 2;
                new_game = 1;

            }
            if (draw_wall(LCD_X/2, 7, 0, 24)) {
                lives--;
                length = 2;
                new_game = 1;

            }
            if (draw_wall(LCD_X/3*2, LCD_Y/3*2, 27, 0)) {
                lives--;
                length = 2;
                new_game = 1;
            }

        }
        // magic side and top teleportation
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

        if (sprites_collided()) {
            if (walls == 1) {
                score += 2;
            } else {
                // increment score
                score++;

            }
            // increment length
            length++;
            respawn_food(score+length);

            init_sprite(&snake[length], snake[length-2].x, snake[length-2].y, 3, 3, snake_bitmap);

        }


        //step snake
        snake_step();
        // update screen
        show_screen();
        adc_result = adc_read(1);      // read adc value at PA0
        if (0 >= adc_result && adc_result <= 250) {
            _delay_ms(200);
        } else if (251 >= adc_result && adc_result <= 450) {
            _delay_ms(190);
        } else if (451 >= adc_result && adc_result <= 650) {
            _delay_ms(180);
        } else if (651 >= adc_result && adc_result <= 850) {
            _delay_ms(170);
        } else if (851 >= adc_result && adc_result <= 1000) {
            _delay_ms(160);
        }


    }
    //clear any characters that were written on the screen
    clear_screen();

    ////array is too big for the screen size, so we break it into 3 parts
    draw_string(5,15,"Game Over");

    //write the string on the lcd
    show_screen();


    return 0;
}
