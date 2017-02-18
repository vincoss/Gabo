#include <avr/io.h>				
#include <stdlib.h>
#include "Usart.h"

void UsartInitialize(void)
{
	// Load upper 8- bits of the baud rate value into the high byte of the UBRR register
	UBRR0H = (uint8_t)(USART_BAUD_PRESCALLER >> 8);
	// Load lower 8- bits of the baud rate value into the low byte of the UBRR register
	UBRR0L = (uint8_t)(USART_BAUD_PRESCALLER);
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	UCSR0C = ((1 << UCSZ00) | (1 << UCSZ01));
}

void UsartWriteChar(unsigned char data)
{
	while (!(UCSR0A & (1 << UDRE0)));
	UDR0 = data;
}

unsigned char UsartReadChar(void)
{
	while (!(UCSR0A & (1 << RXC0)));
	return UDR0;
}

void UsartWriteCharString(char* stringPtr)
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