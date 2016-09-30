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
char walls = 0;

char new_game = 1;

Sprite *snake;
Sprite food;
unsigned char snake_bitmap [] = {
    0b01000000,
    0b11100000,
    0b01000000,
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

    for (int i = 1; i <= 2+score; i++) {
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
    init_sprite(&snake[1], snake[0].x-4, y, 3, 3, snake_bitmap);
}

void snake_step() {

    for (int i = 1; i <= 2+score; i++) {
        if (snake[0].x == snake[i].x && snake[0].y == snake[i].y && new_game == 0) {
            lives--;
            new_game = 1;
            return;

        }
    }
    for (int k = 1+score; k > 0; k--){ 
        snake[k].x = snake[k-1].x;
        snake[k].y = snake[k-1].y;
    }

    snake[0].x += snake[0].dx;
    snake[0].y += snake[0].dy;


}

void draw_walls() {

}

void draw_snake() {
    for (int i = 0; i < 2+score; i++) {
        draw_sprite(&snake[i]);
    }

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

   snake = (Sprite*) malloc(2 * sizeof(Sprite));


   snake[0].dx = 0;
   snake[0].dy = 0;

    unsigned char food_bitmap [] = {
        0b01000000,
        0b11100000,
        0b01000000,

    };


    init_sprite(&food, 42, 12, 3, 3, food_bitmap);


    while(1){
        clear_screen();
        draw_score();
        if (new_game == 1) {
            respawn_snake(24);
            respawn_food(21221);
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


        int snake_x = round(snake[0].x);
        int snake_y = round(snake[0].y);
        int food_x = round(food.x);
        int food_y = round(food.y);

        if (walls == 1) {
            draw_walls();
        }
        if (snake_x <= -1) {
            snake[0].x = 84;
        }
        if (snake_x >= 85) {
            snake[0].x = 0;

        }
        if (snake_y <= 7) {
            snake[0].y = 48;
        }
        if (snake_y >= 49) {
            snake[0].y = 8;
        }

        if (snake_x  == food_x && snake_y == food_y) {
            if (walls == 1) {
                score += 2;
            } 
            score++;
            respawn_food(score+food.y);
            snake = (Sprite*) realloc(snake, (2+score)*sizeof(Sprite));

            init_sprite(&snake[1+score], snake[1].x, snake[1].y, 3, 3, snake_bitmap);

        }

        snake_step();
        show_screen();
        _delay_ms(50);



    }


    return 0;
}
