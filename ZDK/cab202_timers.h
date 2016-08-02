/*
 *	cab202_timer_h: Defines portable functions for pausing execution
 *	and determining if a specified interval has elapsed.
 *
 *	Copyright (C) Queensland University of Technology, 2015.
 *
 *	$Revision:Sun Jul 24 19:36:39 EAST 2016$
 */

#ifndef __TIMER_H__
#define __TIMER_H__

#include <stdbool.h>
#include <stdio.h>

/*	Constant number of milliseconds in a second. */
#define MILLISECONDS 1000

/*	Data structure to keep track of elapsed time. */
typedef struct {
	double reset_time;
	long milliseconds;
} cab202_timer_t;

/*	Data type to represent unique timer ID. */
typedef cab202_timer_t * timer_id;

/**
 *	create_timer:
 *
 *	Creates a new timer and sets it up with the required interval.
 *
 *	Input:
 *	-  milliseconds: the length of the desired interval between reset and expiry.
 *
 *	Output:
 *		Returns the address of the timer which can be used to check the status 
 *		of the timer. 
 */
timer_id create_timer( long milliseconds );

/**
 *	Deallocates resources associated with the timer.
 *
 *	Input:
 *		timer: the address of a timer to be deallocated.
 */
void destroy_timer( timer_id timer );

/*
 *	timer_reset:
 *
 *	Reset a timer to start a new interval.
 *
 *	Input:
 *	-	timer: the address of a timer which is to be reset.
 *
 *	Output: void.
 */
void timer_reset( timer_id id );

/*
 *	timer_expired:
 *
 *	Checks a timer to see if the associated interval has passed. If the interval has
 *	elapsed, the timer is reset automatically, ready to start again.
 *
 *	Input:
 *	-	id: The address of a to check and update.
 *
 *	Output:
 *		Returns TRUE if and only if the interval had elapsed.
 */
bool timer_expired( timer_id timer );

/**	
 *	timer_pause:
 *
 *	Pauses execution in a system-friendly way to allow other processes to work and
 *	conserve clock cycles.
 *
 *	Input:
 *		milliseconds:	The duration of the desired pause.
 *
 *	Output: void.
 */
void timer_pause( long milliseconds );

/**
 *	get_current_time:
 *
 *	Gets an estimate of the time elapsed since 01/01/1970 with 
 *	microsecond accuracy.
 *
 *	Input: void.
 *
 *	Output: Returns the current system time in measured in whole and fractional seconds.
 */
double get_current_time( void );

// ------------------------------------------------------------------
//	Advanced facilities to support automated testing.
// ------------------------------------------------------------------

/**
 *	Override: timer_pause().
 *
 *	This callback function, if not NULL, is used in place 
 *	of the default implementation of timer_pause(). A typical
 *	application would be to erase or fake a delay to allow a 
 *	test which depends on passage of time to execute rapidly.
 *
 *	If you use this function override, you should most likely
 *	also override get_current_time().
 *
 *	Input:
 *		milliseconds: The duration of the desired pause.
 *
 *	Output: void.
 *
 *	NOTE: This function is for internal use only. User code should NOT call 
 *	this function pointer directly.
 */
void( *zdk_timer_pause )( long milliseconds );

/**
 *	Override: get_current_time().
 *
 *	This callback function, if not NULL, is used in place 
 *	of the default implementation of timer_pause(). A typical
 *	application would be to erase or fake a delay to allow a 
 *	test which depends on passage of time to execute rapidly.
 *
 *	If you use this function override, you should most likely
 *	also override timer_pause().
 *
 *	Input: void.
 *
 *	Output: Returns a value which is treated as the "current 
 *			system time", measured in whole and fractional seconds.
 *
 *	NOTE: This function is for internal use only. User code should NOT call
 *	this function pointer directly.
 */
double( *zdk_get_current_time )( void );

/**
 *	Determines if two timers have the same reset time and expiry period.
 *
 *	Input:
 *		a - The address of a timer to be compared with another.
 *		b - the address of the other timer.
 *
 *	Output: Returns true if and only if the delay and reset times of a and b 
 *	are identical.
 */
bool timers_equal( const cab202_timer_t * a, const cab202_timer_t * b );

/**
 *	Emits a text representation of the state of a designated timer to an
 *	output stream.
 *
 *	Input:
 *		stream - The address of a stream to which the data will be written.
 *		label - A literal which is displayed to help add context to the data.
 *		timer - The address of the timer from which state data is to be 
 *				obtained.
 */
void dump_timer( FILE * stream, const char * label, timer_id timer );

#endif
