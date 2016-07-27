#pragma once

#include <stdbool.h>
#include <stdio.h>

/* 
 * ------------------------------------------------------------
 * File: cab202_sprites.h
 *
 * Simple character-based "graphics" library for CAB202, 2016 semester 2.
 *
 *	Authors:
 *	 	Lawrence Buckingham, Ben Talbot
 *
 *	$Revision:Sun Jul 24 19:36:39 EAST 2016$
 * ------------------------------------------------------------
 */

/*
 *	Data structure used to manage and render moving sprites.
 *
 *	Members:
 *		x, y:	The location of the sprite, represented as double to allow
 *				fractional positioning.
 *
 *		width:	The width of the sprite. This must be less than or equal to 
 *				SS_WIDTH.
 *
 *		height:	The height of the sprite. This must be less than or equal to 
 *				SS_HEIGHT.
 *
 *		dx, dy: A pair of floating point values which store a displacement 
 *				vector. Each time the sprite location is updated by sprite_step
 *				these values are added to the sprite's current x and y 
 *				coordinates.
 *
 *		is_visible: Current visibility of the sprite. true == visible; false == invisible.
 *
 *		bitmap: an array of characters that represents the image. ' ' (space) is 
 *				treated as transparent.
 *
 *		cookie: An arbitrary pointer which can be used to attach additional application-
 *				specific data to the sprite.
 */

typedef struct Sprite {
	int width;
	int height;
	double x, y, dx, dy;
	bool is_visible;
	char * bitmap;
	void * cookie;
} Sprite;

/* 
 *	Data type to uniquely identify all registered sprites. 
 */

typedef Sprite * sprite_id;

/*
 *	Dynamically allocate and initialise a sprite.
 *
 *	Input:
 *		x, y:	The initial location of the sprite. Floating point values are
 *				used to allow sub-pixel resolution (in a chunky display),
 *				making it easier to achieve "smooth" movement.
 *
 *		width, height: The dimensions of the sprite.
 *
 *		bitmap:	The characters to show. A dynamically allocated copy of the bitmap
 *				is created. If you alter the bitmap pointer later, care must be taken 
 *				to ensure that memory resources are preserved, restored and deallocated 
 *				correctly.
 *
 *	Output:
 *		Returns the address of a dynamically allocated, initialised, sprite object.
 */

sprite_id sprite_create( double x, double y, int width, int height, char image[] );

/*
 *	Initialise a sprite.
 *
 *	Input:
 *		x, y:	The initial location of the sprite. Floating point values are
 *				used to allow sub-pixel resolution (in a chunky display),
 *				making it easier to achieve "smooth" movement.
 *
 *		width, height: The dimensions of the sprite.
 *
 *		image:	The characters to show. A dynamically allocated copy of the bitmap
 *				is created. If you alter the bitmap pointer later, care must be taken
 *				to ensure that memory resources are preserved, restored and deallocated
 *				correctly.
 *
 *	Output:
 *		n/a
 */
void sprite_init( sprite_id sprite, double x, double y, int width, int height, char image [] );

/*
 *	Releases the memory resources being used by a sprite.
 *
 *	Only call this function if the sprite was created by
 *	calling sprite_create.
 */
void sprite_destroy( sprite_id sprite );

/*
 *	Draws the sprite image. The top left corner of the (rectangular)
 *	bitmap is drawn at the screen coordinate closest to the (x,y)
 *	position of the sprite. Blank characters are treated as transparent.
 *
 *	Input:
 *	-	id: The ID of the sprite which is to be made visible.
 *
 *	Output:
 *	-	n/a
 */
void sprite_draw( sprite_id id );

/*
 *	Sets the stored displacement vector of a 
 *	designated sprite to a new value.
 *
 *	Input:
 *		sprite: the ID of a sprite.
 *		dx, dy: the x- and y- components of the 
 *					new displacement vector.
 */
void sprite_turn_to( sprite_id sprite, double dx, double dy );

/*
 *	Updates the internally stored displacement vector. This is the step 
 *	that is taken when the sprite moves forward or backward.
 *
 *	The new direction is relative to the previous direction. If the old 
 *	direction is 0,0 then the new one will also be 0,0.
 *
 *	Input:
 *		sprite: The ID of a sprite.
 *		degrees: The angle to turn, measured in degrees.
 */
void sprite_turn( sprite_id sprite, double degrees );

/*
 *	Moves the designated sprite to a new absolute location.
 *
 *	Input:
 *		sprite: The ID of a sprite.
 *
 *	Output:
 *		Returns true if and only if the sprite occupies a different
 *		screen position after the move than before the move.
 */
bool sprite_move_to( sprite_id sprite, double x, double y );

/*
 *	Updates the sprite's location, adding the internally stored dx
 *	value to x and the internally stored dy to y.
 *
 *	Input:
 *		sprite: The ID of a sprite.
 *
 *	Output:
 *		Returns true if and only if the sprite occupies a different
 *		screen position after the move than before the move.
*/
bool sprite_step( sprite_id sprite );

/*
 *	Updates the sprite's location, subtracting the internally stored dx
 *	value from x and the internally stored dy from y.
 *
 *	Input:
 *		sprite: The ID of a sprite.
 *
 *	Output:
 *		Returns true if and only if the sprite occupies a different
 *		screen position after the move than before the move.
 */
bool sprite_back( sprite_id sprite );

/*
 *	Updates the sprite's location, adding dx to x and dy to y.
 *
 *	Input:
 *		sprite: The ID of a sprite.
 *		dx: The amount to move in the x-direction.
 *		dy: the amount to move in the y-direction.
 *
 *	Output:
 *		Returns true if and only if the sprite occupies a different
 *		screen position after the move than before the move.
 */
bool sprite_move( sprite_id sprite, double dx, double dy );

/*
 *	Gets the width of the sprite bitmap.
 *
 *	Input:
 *		sprite: The ID of a sprite.
 *
 *	Output:
 *		Returns  the width of the sprite.
 */
int sprite_width( sprite_id sprite );

/*
 *	Gets the height of the sprite bitmap. 
 *
 *	Input:
 *		sprite: The ID of a sprite.
 *
 *	Output:
 *		Returns the height of the sprite.
 */
int sprite_height( sprite_id sprite );

/*
 *	Gets the current x coordinate of the sprite.
 *
 *	Input:
 *		sprite: The ID of a sprite.
 *
 *	Output:
 *		Returns the x position of the sprite.
 */
double sprite_x( sprite_id sprite );

/*
 *	Gets the current y-coordinate of the sprite bitmap.
 *
 *	Input:
 *		sprite: The ID of a sprite.
 *
 *	Output:
 *		Returns the y position of the sprite.
 */
double sprite_y( sprite_id sprite );

/*
 *	Get the current step-size in the x-direction.
 *
 *	Input:
 *		sprite: The ID of a sprite.
 *
 *	Output:
 *		Returns the horizontal component of the sprite's displacement vector.
 */
double sprite_dx( sprite_id sprite );

/*
 *	Get the current step-size in the y-direction.
 *
 *	Input:
 *		sprite: The ID of a sprite.
 *
 *	Output:
 *		Returns the vertical component of the sprite's displacement vector.
 */
double sprite_dy( sprite_id sprite );

/*
 *	Makes a sprite visible.
 *
 *	Input:
 *		sprite: The ID of a sprite.
 *
 *	Output:
 *		Returns true if and only if the visibility of the sprite has changed.
 */
bool sprite_show( sprite_id sprite );

/*
 *	Makes a sprite invisible.
 *
 *	Input:
 *		sprite: The ID of a sprite.
 *
 *	Output:
 *		Returns true if and only if the visibility of the sprite has changed.
 */
bool sprite_hide( sprite_id sprite );

/*
 *	Returns true if and ony if the designated sprite is visible.
 *
 *	Input:
 *		sprite: The ID of a sprite.
 *
 *	Output:
 *		Returns true if and ony if the designated sprite is visible.
 */
bool sprite_visible( sprite_id sprite );

/*
 *	Updates the pattern of characters displayed when the designated 
 *	sprite is rendered.
 *
 *	Input:
 *		sprite: The ID of a sprite.
 *		image: a string containing the new "bitmap" to be displayed.
 */
void sprite_set_image( sprite_id sprite, char image [] );

/**
 *	Compares two sprites to determine if their contents are equal.
 *	This is a deep comparison, not a simple pointer equality test.
 *	If you want only to know if two pointers refer to the same sprite,
 *	use pointer equality test instead.
 *
 *	Input:
 *		a - The address of one sprite to be compared.
 *		b - The address of another sprite to be compared.
 *
 *	Output:	Returns true if and only if all members of the sprite
 *			are equal. Note that sprite cookies are compared by a 
 *			simple pointer equality test.
 */
bool sprites_equal( const sprite_id a, const sprite_id b );

/**
*	Emits a text representation of the state of a designated sprite to an
*	output stream.
*
*	Input:
*		stream - The address of a stream to which the data will be written.
*		label - A literal which is displayed to help add context to the data.
*		sprite - The address of the timer from which state data is to be
*				obtained.
*/
void sprite_dump( FILE * stream, const char label [], sprite_id sprite );
