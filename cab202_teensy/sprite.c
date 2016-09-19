/*
 *  CAB202 Teensy Library (cab202_teensy)
 *	sprite.c
 *
 *	B.Talbot, September 2015
 *	Queensland University of Technology
 */
#include <math.h>
#include "sprite.h"
#include "lcd.h"
#include "graphics.h"

void init_sprite(Sprite* sprite, float x, float y, unsigned char width, unsigned char height, unsigned char* bitmap ) {
	// Apply supplied values
	sprite->x = x;
	sprite->y = y;
	sprite->width = width;
	sprite->height = height;
	sprite->bitmap = bitmap;	// This is only a SHALLOW copy!!!

	// Enforce some default values for sanity
	sprite->is_visible = 1;
	sprite->dx = 0.0f;
	sprite->dy = 0.0f;
}

void draw_sprite(Sprite* sprite ) {
	// Do nothing if not visible
	if (!sprite->is_visible) {
		return;
	}

	// Loop through the bit-packed bitmap data, drawing each individual bit
	// (assume that the bitmap size is h * ceil(w/8))
	unsigned char dx, dy, byte_width = ceil(sprite->width / 8.0f);
	for (dy = 0; dy<sprite->height; dy++) {
		for (dx = 0; dx<sprite->width; dx++) {
			set_pixel(
				(unsigned char) sprite->x+dx,
				(unsigned char) sprite->y+dy,
				(sprite->bitmap[(int) (dy*byte_width+floor(dx/8.0f))] >> (7 - dx%8)) & 1 // ouch...
			);
		}
	}
}
