#ifndef GABO_IO_H
#define GABO_IO_H 1

#include <inttypes.h>

#define TRUE 1
#define FALSE 0

#define GABOIO_SPI_DATA				(1<<PB3)	// MOSI (SI)
#define GABOIO_SPI_CLOCK			(1<<PB5)	//SCK  (SCK)
#define GABOIO_SPI_SET_LATCH_LOW	(PORTB &= ~(1 << PB2))	// Activate slave
#define GABOIO_SPI_SET_LATCH_HIGH	(PORTB |= (1 << PB2))	// Deactivate slave

#define POWERTRAIN_COMMAND			0
#define POWERTRAIN_SPEED_COMMAND	1

// Command variables
volatile unsigned char data_in[8];
volatile unsigned char command_in[8];
volatile unsigned char data_count;
volatile unsigned char command_ready;

volatile uint8_t powerCommand;
volatile uint8_t powertrainCommand;


#endif
