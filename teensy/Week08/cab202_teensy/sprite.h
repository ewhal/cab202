/*
 *  CAB202 Teensy Library (cab202_teensy)
 *	sprite.h
 *
 *	B.Talbot, September 2015
 *	Queensland University of Technology
 */
#ifndef SPRITE_H_
#define SPRITE_H_

/*
 * 	Sprite type definition
 */
typedef struct sprite {
	float x, y, dx, dy;				// Position of top-left sprite corner, and velocities
	unsigned char width, height;	// Pixel width and height of sprite
	unsigned char is_visible;		// Boolean visibility of sprite
	unsigned char *bitmap;			// Bit-packed pixel data (should be h*ceil(w/8) bytes long!)
} Sprite;

/*
 * 	Functions for initialising and drawing a sprite pointer
 *  (there is only a SHALLOW copy of the bitmap!!!)
 */
void init_sprite(Sprite* sprite, float x, float y, unsigned char width, unsigned char height, unsigned char* bitmap );

void draw_sprite(Sprite* sprite);

#endif /* SPRITE_H_ */
