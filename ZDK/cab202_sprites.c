/*
 * ------------------------------------------------------------
 * File: cab202_sprites.c
 *
 * Simple character-based "graphics" library for CAB202, 2016 semester 2.
 *
 *	Authors:
 *	 	Lawrence Buckingham, Ben Talbot
 *
 *	$Revision:Sun Jul 24 19:36:39 EAST 2016$
 * ------------------------------------------------------------
 */

#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "cab202_graphics.h"
#include "cab202_sprites.h"
#include "curses.h"

/*
*	Dynamically create and initialise a sprite.
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

sprite_id sprite_create( double x, double y, int width, int height, char image[] ) {
	assert( width > 0 );
	assert( height > 0 );
	assert( image != NULL );

	sprite_id sprite = malloc( sizeof( Sprite ) );

	if ( sprite != NULL ) {
		sprite_init( sprite, x, y, width, height, image );
	}

	return sprite;
}

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
 *		image:	The characters to show. The address of the image is saved directly,
 *				enabling efficient page-flipping animation.
 *
 *	Output:
 *		n/a
 */
void sprite_init( sprite_id sprite, double x, double y, int width, int height, char image[] ) {
	assert( width > 0 );
	assert( height > 0 );
	assert( image != NULL );
	assert( sprite != NULL );

	sprite->is_visible = TRUE;
	sprite->x = x;
	sprite->y = y;
	sprite->width = width;
	sprite->height = height;
	sprite->dx = 0;
	sprite->dy = 0;
	sprite->bitmap = image;
	sprite->cookie = NULL;
}

/*
 *	Releases the memory resources being used by a sprite.
 *
 *	Only call this function if the sprite was created by
 *	calling sprite_create.
 */

void sprite_destroy( sprite_id sprite ) {
	if ( sprite != NULL ) {
		free( sprite );
	}
}


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
void sprite_draw( sprite_id sprite ) {
	assert( sprite != NULL );

	if ( !sprite->is_visible ) return;

	int x = (int) round( sprite->x );
	int y = (int) round( sprite->y );
	int offset = 0;

	for ( int row = 0; row < sprite->height; row++ ) {
		for ( int col = 0; col < sprite->width; col++ ) {
			char ch = sprite->bitmap[offset++] & 0xff;

			if ( ch != ' ' ) {
				draw_char( x + col, y + row, ch );
			}
		}
	}
}

/*
 *	Sets the stored displacement vector of a 
 *	designated sprite to a new value.
 *
 *	Input:
 *		sprite: the ID of a sprite.
 *		dx, dy: the x- and y- components of the 
 *					new displacement vector.
 */
void sprite_turn_to( sprite_id sprite, double dx, double dy ) {
	assert( sprite != NULL );
	sprite->dx = dx;
	sprite->dy = dy;
}

/*
 *	sprite_turn:
 *
 *	Sets the internally stored direction. That is, the step that is taken when
 *	the sprite moves forward or backward.
 *
 *	The new direction is relative to the old one. If the old direction is 0,0 then
 *	the new one will also be 0,0.
 *
 *	Input:
 *		sprite: The ID of a sprite.
 *		degrees: The angle to turn, measured in degrees.
 */
void sprite_turn( sprite_id sprite, double degrees ) {
	double radians = degrees * M_PI / 180;
	double s = sin( radians );
	double c = cos( radians );
	double dx = c * sprite->dx + s * sprite->dy;
	double dy = -s * sprite->dx + c * sprite->dy;
	sprite->dx = dx;
	sprite->dy = dy;
}


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
bool sprite_move_to( sprite_id sprite, double x, double y ) {
	assert( sprite != NULL );
	int x0 = round( sprite->x );
	int y0 = round( sprite->y );
	sprite->x = x;
	sprite->y = y;
	int x1 = round( sprite->x );
	int y1 = round( sprite->y );
	return ( x1 != x0 ) || ( y1 != y0 );
}

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
bool sprite_step( sprite_id sprite ) {
	assert( sprite != NULL );
	int x0 = round( sprite->x );
	int y0 = round( sprite->y );
	sprite->x += sprite->dx;
	sprite->y += sprite->dy;
	int x1 = round( sprite->x );
	int y1 = round( sprite->y );
	return ( x1 != x0 ) || ( y1 != y0 );
}

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
bool sprite_back( sprite_id sprite ) {
	assert( sprite != NULL );
	int x0 = round( sprite->x );
	int y0 = round( sprite->y );
	sprite->x -= sprite->dx;
	sprite->y -= sprite->dy;
	int x1 = round( sprite->x );
	int y1 = round( sprite->y );
	return ( x1 != x0 ) || ( y1 != y0 );
}

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
bool sprite_move( sprite_id sprite, double dx, double dy ) {
	assert( sprite != NULL );
	int x0 = round( sprite->x );
	int y0 = round( sprite->y );
	sprite->x += dx;
	sprite->y += dy;
	int x1 = round( sprite->x );
	int y1 = round( sprite->y );
	return ( x1 != x0 ) || ( y1 != y0 );
}

/*
 *	Gets the width of the sprite bitmap.
 *
 *	Input:
 *		sprite: The ID of a sprite.
 *
 *	Output:
 *		Returns the width of the sprite.
 */
int sprite_width( sprite_id sprite ) {
	assert( sprite != NULL );
	return sprite->width;
}

/*
 *	Gets the height of the sprite bitmap.
 *
 *	Input:
 *		sprite: The ID of a sprite.
 *
 *	Output:
 *		Returns the height of the sprite.
 */
int sprite_height( sprite_id sprite ) {
	assert( sprite != NULL );
	return sprite->height;
}

/*
 *	Gets the current x coordinate of the sprite.
 *
 *	Input:
 *		sprite: The ID of a sprite.
 *
 *	Output:
 *		Returns the x position of the sprite.
 */
double sprite_x( sprite_id sprite ) {
	assert( sprite != NULL );
	return sprite->x;
}

/*
 *	Gets the current y-coordinate of the sprite bitmap.
 *
 *	Input:
 *		sprite: The ID of a sprite.
 *
 *	Output:
 *		Returns the y position of the sprite.
 */
double sprite_y( sprite_id sprite ) {
	assert( sprite != NULL );
	return sprite->y;
}

/*
 *	Get the current step-size in the x-direction.
 *
 *	Input:
 *		sprite: The ID of a sprite.
 *
 *	Output:
 *		Returns the horizontal component of the sprite's displacement vector.
 */
double sprite_dx( sprite_id sprite ) {
	assert( sprite != NULL );
	return sprite->dx;
}

/*
 *	Get the current step-size in the y-direction.
 *
 *	Input:
 *		sprite: The ID of a sprite.
 *
 *	Output:
 *		Returns the vertical component of the sprite's displacement vector.
 */
double sprite_dy( sprite_id sprite ) {
	assert( sprite != NULL );
	return sprite->dy;
}

/*
 *	Makes a sprite visible.
 *
 *	Input:
 *		sprite: The ID of a sprite.
 *
 *	Output:
 *		Returns true if and only if the visibility of the sprite has changed.
*/
bool sprite_show( sprite_id sprite ) {
	assert( sprite != NULL );
	bool old_val = sprite->is_visible;
	sprite->is_visible = true;
	return ! old_val;
}

/*
 *	Makes a sprite invisible.
 *
 *	Input:
 *		sprite: The ID of a sprite.
 *
 *	Output:
 *		Returns true if and only if the visibility of the sprite has changed.
 */
bool sprite_hide( sprite_id sprite ) {
	assert( sprite != NULL );
	bool old_val = sprite->is_visible;
	sprite->is_visible = false;
	return old_val;
}

/*
 *	Check whether a designated sprite is visible, that is, will it be displayed
 *	by draw_sprite.
 *
 *	Input:
 *		sprite: The ID of a sprite.
 *
 *	Output:
 *		Returns true if and ony if the designated sprite is visible.
 */
bool sprite_visible( sprite_id sprite ) {
	assert( sprite != NULL );
	return sprite->is_visible;
}

/*
*	Updates the pattern of characters displayed when the designated
*	sprite is rendered.
*
*	Input:
*		sprite: The ID of a sprite.
*		image: a string containing the new image to be displayed.
*/
void sprite_set_image( sprite_id sprite, char image[] ) {
	assert( sprite != NULL );
	assert( image != NULL );
	sprite->bitmap = image;
}

// ---------------------------------------------------------------------------

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
void sprite_dump( FILE * stream, const char label[], sprite_id sprite ) {
	if ( !sprite ) {
		fprintf( stream, "%s: NULL pointer\n", label );
		return;
	}

	fprintf( stream, "%s->%s: %f\n", label, "x", sprite->x );
	fprintf( stream, "%s->%s: %f\n", label, "y", sprite->y );
	fprintf( stream, "%s->%s: %d\n", label, "width", sprite->width );
	fprintf( stream, "%s->%s: %d\n", label, "height", sprite->height );
	fprintf( stream, "%s->%s: %f\n", label, "dx", sprite->dx );
	fprintf( stream, "%s->%s: %f\n", label, "dy", sprite->dy );
	fprintf( stream, "%s->%s: %s\n", label, "is_visible", sprite->is_visible ? "true" : "false" );
	fprintf( stream, "%s->%s: (((", label, "bitmap" );

	if ( sprite->bitmap == NULL ) {
		fprintf( stream, "NULL" );
	}
	else {
		for ( int i = 0; i < sprite->width * sprite->height; i++ ) {
			fprintf( stream, "%c", sprite->bitmap[i] );
		}
	}

	fprintf( stream, ")))\n" );
	fprintf( stream, "\n" );
}

// ---------------------------------------------------------------------------

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
bool sprites_equal( const sprite_id a, const sprite_id b ) {
	if ( a == b )  return true;
	if ( a == NULL && b != NULL ) return false;
	if ( a != NULL && b == NULL ) return false;
	if ( a->x != b->x ) return false;
	if ( a->y != b->y ) return false;
	if ( a->dx != b->dx ) return false;
	if ( a->dy != b->dy ) return false;
	if ( a->is_visible != b->is_visible ) return false;
	if ( a->width != b->width ) return false;
	if ( a->height != b->height ) return false;
	if ( strncmp( a->bitmap, b->bitmap, a->width*a->height ) != 0 ) return false;
	if ( a->cookie != b->cookie ) return false;
	return true;
}
