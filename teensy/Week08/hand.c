#include <avr/io.h>
#include <math.h>
#include "cpu_speed.h"
#include "graphics.h"
#include "lcd.h"
#include <util/delay.h>

int main(){
    set_clock_speed(CPU_8MHz);
    //switch the back LEDs lights on    
    DDRC  |= 1 << PIN7;
    PORTC |= 1 << PIN7;
    DDRB |= 1 << PIN7;

    lcd_init(LCD_DEFAULT_CONTRAST);

    clear_screen();
    // start the line from the center of the screen
    int x0 = LCD_X/2;
    int y0 = LCD_Y/2;
    int x1 = 0;
    int y1 = 0;
    // the length oh the hand is 24
    int r = 24;

    for (int i=0 ; i<360; i+=6){
       clear_screen();
       // the end point on a circle with 6 degrees step
       x1 = x0 + round(r * cos(i * M_PI/180));
       y1 = y0 + round(r * sin(i * M_PI/180));
       //
       draw_line(x0,y0,x1,y1);
       show_screen();
       _delay_ms(1000);
    }

    return 0;
}
