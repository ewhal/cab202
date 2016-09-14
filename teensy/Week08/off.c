#include <avr/io.h>

int main() {
    DDRB = DDRB | 0b00000100;

    DDRF = DDRF | 0b11011111;

    while (1) {

        if ((PINF >> 5 ) & 0b1) {
            PORTB = PORTB | 0b00000100;

        } 
    }


    return 0;

}
