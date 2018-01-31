/*
 * Usart.c
 *
 * Created: 29/01/2018 10:10:40 PM
 *  Author: Ferdinand Lukasak
 */ 

#include <avr/io.h>
#include "Usart.h"


void UsartInitialize(void)
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

void UsartWriteChar(unsigned char data)
{
	while (!(UCSR0A & (1 << UDRE0))); // wait while register is free
	UDR0 = data; // load data in the register
}

unsigned char UsartReadChar(void)
{
	while (!(UCSR0A & (1 << RXC0))); // wait while data is being received
	return UDR0; // return 8-bit data
}

void UsartWriteCharString(unsigned char* stringPtr)
{
	// Here we check if there is still more chars to send, this is done checking the actual char and see if it is different from the null '\n' char
	while (*stringPtr != 0x00)
	{
		// Using the simple send function we send one char at a time
		UsartWriteChar(*stringPtr);

		// We increment the pointer so we can read the next char
		stringPtr++;
	}
}

