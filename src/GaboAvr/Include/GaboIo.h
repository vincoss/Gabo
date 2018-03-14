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

#define GABOIO_SPI_DATA					(1<<PB3)	// MOSI (SI)
#define GABOIO_SPI_CLOCK				(1<<PB5)	//SCK  (SCK)
#define GABOIO_SPI_OUTPUT_LATCH_PINB2	PB2	// Output
#define GABOIO_SPI_INPUT_LATCH_PINB4	PB4	// Input
#define GABOIO_SPI_SET_OUTPUT_LATCH_LOW		(PORTB &= ~(1 << GABOIO_SPI_OUTPUT_LATCH_PINB2))	// Activate slave
#define GABOIO_SPI_SET_OUTPUT_LATCH_HIGH	(PORTB |= (1 << GABOIO_SPI_OUTPUT_LATCH_PINB2))		// Deactivate slave
#define GABOIO_SPI_SET_INPUT_LATCH_LOW		(PORTB &= ~(1 << GABOIO_SPI_INPUT_LATCH_PINB4))		// Activate slave
#define GABOIO_SPI_SET_INPUT_LATCH_HIGH	(PORTB |= (1 << GABOIO_SPI_INPUT_LATCH_PINB4))			// Deactivate slave

volatile uint8_t IsOutputInitialized;	// Indicates that output was already set at least one time.

volatile uint8_t powerCommandTemp;		// =Powertrain, PowerTakeOff 00000011
volatile uint8_t powertrainCommandTemp;

volatile uint8_t PowerCommand;		// Store power on/off value
volatile uint8_t PowertrainCommand; // Store powertrain on/off values left and right

volatile int powertrainWorkHours;	// TODO: these should be persited every hour write increment log
volatile int powertakeoffWorkHours; // TODO: these should be persited every hour write increment log

volatile uint8_t startWriteCommand;

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
	
	# Shaft read sensor, current max rpm is 200 then encoder has 50 teeth, the SPI read rate should be high enough to read incoming
	shaft changes = 200*50 = 10,000 per minute
	main loop read SPI bus should around 200 per second
	on/off signals
*/

#define POWERDR   _SFR_IO8(0x31)
#define DRIVE    _SFR_IO8(0x31)
#define PTO    _SFR_IO8(0x31)

/*
	temp
	run

	Begin update command
	
	Z=0	start
	Z=1	end
	
	End update command

*/

// Input
#define PINI0	0	// Hall left
#define PINI1	1	// Hall right

// Output
#define PINO0	0	//  Power A
#define PINO1	1	//  Power B
#define PINO2	2	//  Power C
#define PIN03	3	//  Power D
// Powertrain
#define PINO4	4	// On/Off		(left and right)
#define PINO5	5	// Start/Stop	(left and right)
#define PINO6	6	// Cv/Ccv		(left)
#define PINO7	7	// Cv/Ccv		(right)

#endif
