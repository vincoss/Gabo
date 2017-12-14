#ifndef GaboIo_H
#define GaboIo_H

#include <inttypes.h>

#define TRUE 1
#define FALSE 0

#define GaboIo_Spi_Data			(1<<PB3)	// MOSI (SI)
#define GaboIo_Spi_Clock		(1<<PB5)	//SCK  (SCK)
#define GaboIo_Spi_SetLatchLow	(PORTB &= ~(1 << PB2))	// Activate slave
#define GaboIo_Spi_SetLatchHigh (PORTB |= (1 << PB2))	// Deactivate slave

#define PowertrainCommand		0
#define PowertrainSpeedCommand	1

// Command variables
volatile unsigned char data_in[8];
volatile unsigned char command_in[8];
volatile unsigned char data_count;
volatile unsigned char command_ready;

volatile uint8_t powerCommand;
volatile uint8_t commandPowertrain;


#endif
