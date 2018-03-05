/*
 * GaboIo.h
 *
 * Created: 29/01/2018 10:09:16 PM
 *  Author: Ferdinand Lukasak
 */ 


#ifndef GABO_IO_H_
#define GABO_IO_H_ 1

#include <inttypes.h>

#define TRUE 1
#define FALSE 0

#define GABOIO_SPI_DATA				(1<<PB3)	// MOSI (SI)
#define GABOIO_SPI_CLOCK			(1<<PB5)	//SCK  (SCK)
#define GABOIO_SPI_SET_LATCH_LOW	(PORTB &= ~(1 << PB2))	// Activate slave
#define GABOIO_SPI_SET_LATCH_HIGH	(PORTB |= (1 << PB2))	// Deactivate slave

#define POWERTRAIN_COMMAND			0	// TODO: WHat for? Index?
#define POWERTRAIN_SPEED_COMMAND	1	// TODO: WHat for? Index?

volatile uint8_t powerCommand;		// =Powertrain, PowerTakeOff 00000011
volatile uint8_t powertrainCommand;

volatile int powertrainWorkHours;	// TODO: these should be persited every hour write increment log
volatile int powertakeoffWorkHours; // TODO: these should be persited every hour write increment log

/*
	TODO: add commands flags, startWriteCommand, endWriteCommand
	Those flags shall be used when commands are written, it might take few interactions(CPU cycles) 
	until all commands are written when command write is complete set end writeCommand to true.
	On this stage commands must be pushed from temp variables to program variables.
	
	NOTE: Workhous just use as ticks, then always add, let say every 1 minute write to storage
	
	1. Power 00
	2. drive
	3. take-off power
	
	void processPowerCommand()
	{
		
	}
*/

#define POWERDR   _SFR_IO8(0x31)
#define DRIVE    _SFR_IO8(0x31)
#define PTO    _SFR_IO8(0x31)


#endif
