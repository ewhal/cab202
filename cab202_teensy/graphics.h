/*
 *  CAB202 Teensy Library: 'cab202_teensy'
 *	graphics.h
 *
 *	B.Talbot, September 2015
 *	Queensland University of Technology
 */
#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include "ascii_font.h"
#include "lcd.h"

/*
 *  Size of the screen_buffer based on 1 bit / pixel
 */
#define LCD_BUFFER_SIZE (LCD_X * (LCD_Y / 8))

/*
 *  Local screen_buffer
 *  (accessible from any file that includes graphics.h)
 */
extern unsigned char screen_buffer[LCD_BUFFER_SIZE];

/*
 *  Sole function that interfaces with the LCD hardware
 *  (sends ALL OF current buffer to LCD screen)
 */
void show_screen(void);

/*
 * Core functions for managing the local buffer
 * (clearing every pixel, and setting individual pixels)
 */
void clear_screen(void);
void set_pixel(unsigned char x, unsigned char y, unsigned char value);

/*
 * Extra useful drawing functions that modify the local buffer
 * (lines, characters, and strings)
 */
void draw_line(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2);
void draw_char(unsigned char top_left_x, unsigned char top_left_y, char character);
void draw_string(unsigned char top_left_x, unsigned char top_left_y, char *characters);

#endif /* GRAPHICS_H_ */
