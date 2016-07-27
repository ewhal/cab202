/*
 * cab202_timers.c
 *
 * Simple, portable, timer functionality.
 *
 *	Authors:
 *	 	Lawrence Buckingham
 *
 *	$Revision:Sun Jul 24 19:36:39 EAST 2016$
 */

#include "cab202_timers.h"
#include <assert.h>
#include <stdlib.h>


#ifdef WIN32
#include <windows.h>
#else
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
#endif

#ifdef __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#endif

// ---------------------------------------------------------------------------

timer_id create_timer( long milliseconds ) {
	assert( milliseconds > 0 );

	timer_id timer = malloc( sizeof( cab202_timer_t ) );

	timer->milliseconds = milliseconds;
	timer_reset( timer );

	return timer;
}

// ---------------------------------------------------------------------------

void destroy_timer( timer_id timer ) {
	assert( timer != NULL );

	free( timer );
}

// ---------------------------------------------------------------------------

void timer_reset( timer_id timer ) {
	assert( timer != NULL );

	timer->reset_time = get_current_time();
}

// ---------------------------------------------------------------------------

bool timer_expired( timer_id timer ) {
	assert( timer != NULL );

	double current_time = get_current_time();
	double time_diff = current_time - timer->reset_time;
	int expired = time_diff * MILLISECONDS >= timer->milliseconds;

	if ( expired ) {
		timer_reset( timer );
	}

	return expired;
}

// ---------------------------------------------------------------------------

void( *zdk_timer_pause )( long milliseconds ) = NULL;

// ---------------------------------------------------------------------------

void timer_pause( long milliseconds ) {
	if ( zdk_timer_pause ) {
		zdk_timer_pause( milliseconds );
	}
	else {
#ifdef WIN32
		Sleep( milliseconds );
#else
		/* usleep requires input in microseconds rather than milliseconds. */
		usleep( milliseconds * MILLISECONDS );
#endif
	}
}

// ---------------------------------------------------------------------------

double( *zdk_get_current_time )( void ) = NULL;

// ---------------------------------------------------------------------------

double get_current_time() {

	if ( zdk_get_current_time ) {
		return zdk_get_current_time();
	}
	else {
		struct timespec timeval;

#ifdef __MACH__ // OS X does not have clock_gettime, use clock_get_time
		clock_serv_t cclock;
		mach_timespec_t mts;
		host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
		clock_get_time(cclock, &mts);
		mach_port_deallocate(mach_task_self(), cclock);
		timeval.tv_sec = mts.tv_sec;
		timeval.tv_nsec = mts.tv_nsec;
#else
		/* http://linux.die.net/man/3/clock_gettime */
		clock_gettime( CLOCK_REALTIME, &timeval );
#endif

		return timeval.tv_sec + timeval.tv_nsec / 1.0e+9;
	}
}

// ---------------------------------------------------------------------------

bool timers_equal( const cab202_timer_t * a, const cab202_timer_t * b ) {
	if ( a == b )  return true;
	if ( a == NULL && b != NULL ) return false;
	if ( a != NULL && b == NULL ) return false;
	if ( a->milliseconds != b->milliseconds ) return false;
	if ( a->reset_time != b->reset_time ) return false;
	return true;
}

// ---------------------------------------------------------------------------

void dump_timer( FILE * stream, const char * label, timer_id timer ) {
	if ( !timer ) {
		printf( "%s: NULL pointer\n", label );
		return;
	}

	printf( "%s->%s: %f\n", label, "reset_time", timer->reset_time );
	printf( "%s->%s: %ld\n", label, "milliseconds", timer->milliseconds );
	printf( "\n" );
}

// ---------------------------------------------------------------------------
