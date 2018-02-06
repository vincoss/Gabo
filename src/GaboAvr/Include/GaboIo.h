/*
 * GaboIo.h
 *
 * Created: 29/01/2018 10:09:16 PM
 *  Author: Ferdinand Lukasak
 */ 


#ifndef GABO_IO_H_
#define GABO_IO_H_

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
#define RX_BUFFER_SIZE 8
volatile unsigned char rx_data_in[RX_BUFFER_SIZE];
volatile unsigned char command_in[RX_BUFFER_SIZE];
volatile uint8_t rx_data_count;
volatile uint8_t command_ready;

// This flag is set on USART Receiver buffer overflow
volatile unsigned char rx_buffer_overflow;

volatile uint8_t powerCommand;
volatile uint8_t powertrainCommand;

volatile int powertrainWorkHours;
volatile int powertakeoffWorkHours;

#endif
