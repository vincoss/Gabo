/*
 * GaboUsart.h
 *
 * Created: 29/01/2018 10:09:45 PM
 *  Author: Ferdinand Lukasak
 */ 


#ifndef GABO_USART_H_
#define GABO_USART_H_

#include <avr/io.h>
#include <avr/interrupt.h>

// NOTE: For more information see specification document. RS-232

#ifndef F_CPU
# define F_CPU 16000000UL // Says to the compiler which is our clock frequency, permits the delay functions to be very accurate
#endif

#define USART_BAUDRATE 9600   // The baudrate that we want to use
#define USART_BAUD_PRESCALLER (((( F_CPU / 16UL) + ( USART_BAUDRATE / 2)) / ( USART_BAUDRATE )) - 1)

// These are used with Usart interrupt
#define FRAMING_ERROR		(1 << FE0)
#define PARITY_ERROR		(1 << UPE0)
#define DATA_OVERRUN		(1 << DOR0)

void GaboUsartInitialize(void);
void GaboUsartWriteChar(const unsigned char data);
unsigned char GaboUsartReadChar(void);
void GaboUsartWriteCharString(const unsigned char* StringPtr);
void GaboUsartInterruptInitialize(void);

// TODO: allow pass bauldrate
void GaboUsartInitialize(void)
{
	// Load upper 8- bits of the baud rate value into the high byte of the UBRR register
	UBRR0H = (uint8_t)(USART_BAUD_PRESCALLER >> 8);
	// Load lower 8- bits of the baud rate value into the low byte of the UBRR register
	UBRR0L = (uint8_t)(USART_BAUD_PRESCALLER);
	// Enable receiver and transmitter
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = ((1 << UCSZ00) | (1 << UCSZ01));
}

void GaboUsartWriteChar(const unsigned char data)
{
	while (!(UCSR0A & (1 << UDRE0))); // wait while register is free
	UDR0 = data; // load data in the register
}

unsigned char GaboUsartReadChar(void)
{
	while (!(UCSR0A & (1 << RXC0))); // wait while data is being received
	return UDR0; // return 8-bit data
}

void GaboUsartWriteCharString(const unsigned char* stringPtr)
{
	// Here we check if there is still more chars to send, this is done checking the actual char and see if it is different from the null '\n' char
	while (*stringPtr != 0x00)
	{
		// Using the simple send function we send one char at a time
		GaboUsartWriteChar(*stringPtr);

		// We increment the pointer so we can read the next char
		stringPtr++;
	}
}

// TODO: refactor into Usart.c one initialize just Usart no interrupt and second with interrupt
void GaboUsartInterruptInitialize(void)
{
	UCSR0B |= (1 << RXEN0) | (1 << RXCIE0); // Enable the USART Recieve Complete interrupt ( USART_RX )
	sei(); // Enable the Global Interrupt Enable flag so that interrupts can be processed
}

#endif /* GABO_USART_H_ */
