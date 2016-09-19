/*
 *  CAB202 Teensy Library (cab202_teensy)
 *	macros.h
 *
 *	B.Talbot, September 2015
 *  Queensland University of Technology
 */
#ifndef MACROS_H_
#define MACROS_H_

/*
 *  Setting data directions in a data direction register (DDR)
 */
#define SET_INPUT(portddr, pin)			portddr &= ~(1 << pin)
#define SET_OUTPUT(portddr, pin)		portddr |= (1 << pin)

/*
 *  Writing and reading from ports
 *  (OUTPUT_WRITE is a combination of OUTPUT_LOW & OUTPUT_HIGH)
 */
#define OUTPUT_WRITE(port, pin, value)	port = (port & ~(1 << pin)) | (value << pin)
#define OUTPUT_LOW(port, pin)			port &= ~(1 << pin)
#define OUTPUT_HIGH(port, pin)			port |= (1 << pin)
#define INPUT_READ(port, pin)			port & (1 << pin)

/*
 *	Rudimentary math macros
 */
#define ABS(x) ((x >= 0) ? x : -x)
#define SIGN(x) ((x > 0) - (x < 0))

#endif /* MACROS_H_ */
