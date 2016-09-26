/*
*	File:	blockhead.c
*	Author: Lawrence Buckingham, Queensland University of Technology.
*	Date:	27 April 2015.
*
*	Implementation of the blockhead walking sequence.
*/

#include "friendly_ports.h" 
#include "graphics.h"
#include "byte.h"
#include "sprite.h"
#include <util/delay.h>

void do_the_walk( void );
void update_blockhead( Sprite *the_block );

void walk_the_walk( void ) {
	clear_screen();
	turn_on( LED1 );
	draw_string( 0, 0, "Click to walk..." );
	show_screen();
	wait_until( pressed( SW2 ) );
	_delay_ms(100);
	wait_until( !pressed( SW2 ) );
	turn_off( LED1 );

	do_the_walk();

	clear_screen();
	turn_on( LED1 );
	draw_string( 0, 0, "Walk over." );
	draw_string( 0, 8, "Click to exit..." );
	show_screen();
	wait_until( pressed( SW2 ) );
	_delay_ms(100);
	wait_until( !pressed( SW2 ) );
	turn_off( LED1 );
}

void do_the_walk() {
	// Notes: 
	//	byte is typedef name for unsigned char, defined in byte.h
	//	UINT and BYTE macros provide a standards-compliant way to express
	//	a binary literal ... the 0b00000000 notation supported by gcc is
	//	not defined in the Standard C language.
	static unsigned char bitmap0[] = {
		UINT( 00001111, 10000000 ),
		UINT( 00001000, 10000000 ),
		UINT( 00001000, 10000000 ),
		UINT( 00001111, 10000000 ),
		UINT( 00000010, 00000000 ),
		UINT( 00001111, 10000000 ),
		UINT( 00010010, 01000000 ),
		UINT( 00100010, 00100000 ),
		UINT( 01000010, 00010000 ),
		UINT( 10000010, 00001000 ),
		UINT( 00000010, 00000000 ),
		UINT( 00000101, 00000000 ),
		UINT( 00001000, 10000000 ),
		UINT( 00001000, 10000000 ),
		UINT( 00001000, 10000000 ),
		UINT( 00010000, 01000000 ),
		UINT( 00010000, 01000000 ),
		UINT( 00100000, 00100000 ),
		UINT( 00100000, 00100000 ),
		UINT( 11100000, 00111000 ),
	};
	static byte bitmap3[] = {
		UINT( 00001111, 10000000 ),
		UINT( 00001000, 10000000 ),
		UINT( 00001000, 10000000 ),
		UINT( 00001111, 10000000 ),
		UINT( 00000010, 00000000 ),
		UINT( 00000111, 00000000 ),
		UINT( 00001010, 10000000 ),
		UINT( 00010010, 10000000 ),
		UINT( 00010010, 01000000 ),
		UINT( 00010010, 00100000 ),
		UINT( 00000010, 00000000 ),
		UINT( 00000011, 00000000 ),
		UINT( 00000010, 11000000 ),
		UINT( 00000010, 00100000 ),
		UINT( 00000010, 11000000 ),
		UINT( 00000011, 00000000 ),
		UINT( 00001110, 00000000 ),
		UINT( 00010010, 00000000 ),
		UINT( 00010010, 00000000 ),
		UINT( 00000011, 10000000 ),
	};
	static byte bitmap4[] = {
		UINT( 00000111, 11000000 ),
		UINT( 00000100, 01000000 ),
		UINT( 00000100, 01000000 ),
		UINT( 00000111, 11000000 ),
		UINT( 00000001, 00000000 ),
		UINT( 00000011, 10000000 ),
		UINT( 00001101, 01000000 ),
		UINT( 00110001, 00100000 ),
		UINT( 00010010, 00011000 ),
		UINT( 00000100, 00000000 ),
		UINT( 00000100, 00000000 ),
		UINT( 00000111, 00000000 ),
		UINT( 00000100, 11000000 ),
		UINT( 00000010, 00110000 ),
		UINT( 00000001, 00001000 ),
		UINT( 00000001, 00010000 ),
		UINT( 00000001, 00100000 ),
		UINT( 00000010, 00111000 ),
		UINT( 00000100, 00000000 ),
		UINT( 00001110, 00000000 ),
	};
	static byte bitmap1[] = {
		UINT( 00001111, 10000000 ),
		UINT( 00001000, 10000000 ),
		UINT( 00001000, 10000000 ),
		UINT( 00001111, 10000000 ),
		UINT( 00000010, 00000000 ),
		UINT( 00000111, 00000000 ),
		UINT( 00001010, 10000000 ),
		UINT( 00010010, 10000000 ),
		UINT( 00010010, 01000000 ),
		UINT( 00010010, 00100000 ),
		UINT( 00000010, 00000000 ),
		UINT( 00000111, 00000000 ),
		UINT( 00000101, 00000000 ),
		UINT( 00000100, 10000000 ),
		UINT( 00001000, 01000000 ),
		UINT( 00001000, 00100000 ),
		UINT( 00010000, 00100000 ),
		UINT( 00010000, 00100000 ),
		UINT( 00100000, 00100000 ),
		UINT( 00111000, 00111000 ),
	};
	static byte bitmap2[] = {
		UINT( 00000011, 11100000 ),
		UINT( 00000010, 00100000 ),
		UINT( 00000010, 00100000 ),
		UINT( 00000011, 11100000 ),
		UINT( 00000000, 10000000 ),
		UINT( 00000001, 11000000 ),
		UINT( 00000110, 10100000 ),
		UINT( 00011000, 10010000 ),
		UINT( 00001000, 10011000 ),
		UINT( 00000001, 00000000 ),
		UINT( 00000001, 00000000 ),
		UINT( 00000011, 10000000 ),
		UINT( 00000010, 01000000 ),
		UINT( 00000010, 00100000 ),
		UINT( 00000010, 00010000 ),
		UINT( 00000010, 00001000 ),
		UINT( 00001100, 00010000 ),
		UINT( 00110000, 00010000 ),
		UINT( 00100000, 00100000 ),
		UINT( 00000000, 00111000 ),
	};

#define BITMAP_COUNT 4

	static byte *bitmaps[BITMAP_COUNT] = {bitmap1, bitmap2, bitmap3, bitmap4};

	const int width = 13;
	const int height = sizeof( bitmap0 ) / 2;

	Sprite blockhead;
	init_sprite( &blockhead, (LCD_X - width) / 2, (LCD_Y - height) / 2, width, height, bitmap0 );
	blockhead.dx = 1;
	blockhead.dy = 0;

	clear_screen();
	draw_sprite( &blockhead );
	show_screen();

	db_wait();

	int current_image = 0;
	int walk_counter = 0;

	turn_on( LED0 );
	while ( !pressed( SW2 ) ) {
		clear_screen();
		walk_counter++;

		if ( walk_counter % 10 == 0 ) {
			current_image++;
			current_image %= BITMAP_COUNT;
			blockhead.bitmap = bitmaps[current_image];
		}

		update_blockhead( &blockhead );
		
		draw_sprite( &blockhead );
		show_screen();
		_delay_ms( 20 );
	}
}

void update_blockhead( Sprite *the_block ) {
	the_block->x += the_block->dx;
	the_block->y += the_block->dy;

	if ( the_block->x >= LCD_X ) {
		the_block->x = -the_block->width;
	}

	if ( the_block->y >= LCD_Y ) {
		the_block->y = -the_block->height;
	}
}
