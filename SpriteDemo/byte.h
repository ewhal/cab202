#ifndef __BYTE__
#define __BYTE__

/*
*	File:	byte.h
*	Author: Lawrence Buckingham, Queensland University of Technology.
*	Date:	27 April 2015.
*
*	Portable declaration of byte literals.
*/

typedef unsigned char byte;

// ------------------------------------------------------------------
// Portable byte literal declaration from:
// https://github.com/pkrumins/bithacks.h/blob/master/bithacks.h

#ifdef WIN32
#define HEXIFY(X) 0x##X##LU

#define B8IFY(Y) (((Y&0x0000000FLU)?1:0)  + \
	( ( Y & 0x000000F0LU ) ? 2 : 0 ) + \
	( ( Y & 0x00000F00LU ) ? 4 : 0 ) + \
	( ( Y & 0x0000F000LU ) ? 8 : 0 ) + \
	( ( Y & 0x000F0000LU ) ? 16 : 0 ) + \
	( ( Y & 0x00F00000LU ) ? 32 : 0 ) + \
	( ( Y & 0x0F000000LU ) ? 64 : 0 ) + \
	( ( Y & 0xF0000000LU ) ? 128 : 0 ) )

#define BYTE(Z) ((unsigned char)B8IFY(HEXIFY(Z)))
#else
#define BYTE(Z) (0b##Z)
#endif

#define UINT(x1,x2) BYTE(x1),BYTE(x2)

// End of portable byte macros.
// ------------------------------------------------------------------

#endif