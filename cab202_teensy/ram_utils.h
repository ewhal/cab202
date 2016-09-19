/*
 *  CAB202 Teensy Library (cab202_teensy)
 *	ram_utils.h
 *
 *	J.Luck, May 2015
 *	Queensland University of Technology
 */
#ifndef RAM_UTILS_H_
#define RAM_UTILS_H_

#include <stdlib.h>
#include <avr/io.h>
#include <avr/pgmspace.h>

#define RAM_GUARD 100

/*
 * RAM debugging functions
 */
int estimate_alloc(int len);
int estimate_ram(void);
unsigned char* load_rom_bitmap(const unsigned char* source, int len);
unsigned char* load_rom_string(const unsigned char* source);

#endif /* RAM_H_ */
