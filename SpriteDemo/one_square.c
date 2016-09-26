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
#include "one_square.h"
#include "sprite.h"
#include "friendly_ports.h"
#include "graphics.h"

void update_one_square( Sprite * sprite );

void play_one_square() {
	clear_screen();
	draw_string( 0, 0, "Click right" );
	draw_string( 0, 8, "to play" );
	show_screen();
	wait_until( pressed( SW2 ) );
	_delay_ms(50);
	wait_until( !pressed( SW2 ) );

	_delay_ms( 500 );

	// Notes: 
	//	byte is typedef name for unsigned char, defined in byte.h
	//	UINT and BYTE macros provide a standards-compliant way to express
	//	a binary literal ... the 0b00000000 notation supported by gcc is
	//	not defined in the Standard C language.

	static byte bitmap [] = {
		BYTE( 11111111 ),
		BYTE( 10000001 ),
		BYTE( 10000001 ),
		BYTE( 10000001 ),
		BYTE( 10000001 ),
		BYTE( 10000001 ),
		BYTE( 10000001 ),
		BYTE( 11111111 )
	};

	Sprite sprite;

	init_sprite( &sprite, 0, 0, 8, 8, bitmap );
	srandom( 5198985 );
	double angle = ((double)random()) * 2 * M_PI / RANDOM_MAX;
	sprite.dx = cos( angle );
	sprite.dy = sin( angle );

	while ( ! pressed( SW2 ) ) {
		clear_screen();
		update_one_square( & sprite );
		draw_sprite( &sprite );
		show_screen();
		_delay_ms( 20 );
	}

	clear_screen();
	draw_string( 0, 0, "Game Over" );
	show_screen();

	db_wait();
}

void update_one_square( Sprite * sprite ) {
	sprite->x += sprite->dx;
	sprite->y += sprite->dy;

	if ( sprite->x >= LCD_X - sprite->width || sprite->x < 0 ) {
		sprite->dx = -sprite->dx;
	}

	if ( sprite->y >= LCD_Y - sprite->height || sprite->y < 0 ) {
		sprite->dy = -sprite->dy;
	}
}
