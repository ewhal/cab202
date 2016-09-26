/*
*	File:	one_square.c
*	Author: Lawrence Buckingham, Queensland University of Technology.
*	Date:	27 April 2015.
*
*	Implementation of the functions provided by the one_square "game".
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <util/delay.h>
#include "byte.h"
#include "ten_squares.h"
#include "sprite.h"
#include "friendly_ports.h"
#include "graphics.h"

void setup_ten_squares(
	Sprite sprites[],
	byte *bitmaps[],
	byte widths[],
	byte heights[],
	int sprite_count,
	int bitmap_count
	);
void update_ten_squares( Sprite * sprites );
void draw_ten_squares( Sprite * sprites );
void update_one_square( Sprite * sprite );

void play_ten_squares() {
	clear_screen();
	draw_string( 0, 0, "Click right" );
	draw_string( 0, 8, "to play 10 sq." );
	show_screen();
	wait_until( pressed( SW1 ) );
	_delay_ms(100);
	wait_until( !pressed( SW1 ) );

	_delay_ms( 500 );

	// Notes: 
	//	byte is typedef name for unsigned char, defined in byte.h
	//	UINT and BYTE macros provide a standards-compliant way to express
	//	a binary literal ... the 0b00000000 notation supported by gcc is
	//	not defined in the Standard C language.

	static byte bitmap1[] = {
		BYTE( 11111111 ),
		BYTE( 10000001 ),
		BYTE( 10000001 ),
		BYTE( 10000001 ),
		BYTE( 10000001 ),
		BYTE( 10000001 ),
		BYTE( 10000001 ),
		BYTE( 11111111 )
	};

	static byte bitmap2[] = {
		BYTE( 11111000 ),
		BYTE( 10001000 ),
		BYTE( 10001000 ),
		BYTE( 10001000 ),
		BYTE( 11111000 )
	};

	static byte bitmap3[] = {
		UINT( 11111111, 11110000 ),
		UINT( 10000000, 00010000 ),
		UINT( 10000000, 00010000 ),
		UINT( 10000000, 00010000 ),
		UINT( 10000000, 00010000 ),
		UINT( 10000000, 00010000 ),
		UINT( 10000000, 00010000 ),
		UINT( 11111111, 11110000 )
	};

	byte *bitmaps[3] = { bitmap1, bitmap2, bitmap3 };
	byte widths[] = { 8, 5, 12 };
	byte heights[] = { 8, 5, 8 };

#define SPR_COUNT (10)

	Sprite sprites[SPR_COUNT];
	srandom( 5198985 );

	setup_ten_squares( 
		sprites, bitmaps, widths, heights, 
		SPR_COUNT, 
		sizeof( bitmaps ) / sizeof( bitmaps[0] ) 
	);

	while ( !pressed( SW1 ) ) {
		clear_screen();
		update_ten_squares( sprites );
		draw_ten_squares( sprites );
		show_screen();
		_delay_ms( 50 );
	}

	clear_screen();
	draw_string( 0, 0, "Game Over" );
	show_screen();

	_delay_ms( 500 );
	db_wait();
}

void setup_ten_squares( 
	Sprite sprites[], 
	byte *bitmaps[], 
	byte widths[],
	byte heights[],
	int sprite_count, 
	int bitmap_count 
) {
	for ( int i = 0; i < sprite_count; i++ ) {
		Sprite * sprite = &sprites[i];

		byte * bitmap = bitmaps[i % bitmap_count];
		byte width = widths[i % bitmap_count];
		byte height = heights[i % bitmap_count];

		init_sprite( sprite, 0, 0, width, height, bitmap );
		double angle = ( (double) random( ) ) * 2 * M_PI / RANDOM_MAX;
		sprite->dx = cos( angle );
		sprite->dy = sin( angle );
	}
}

void update_ten_squares( Sprite * sprites ) {
	for ( int i = 0; i < SPR_COUNT; i++ ) {
		update_one_square( sprites + i );
	}
}

void draw_ten_squares( Sprite * sprites ) {
	for ( int i = 0; i < SPR_COUNT; i++ ) {
		draw_sprite( sprites + i );
	}
}
